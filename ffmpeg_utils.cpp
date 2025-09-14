extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libavutil/channel_layout.h>
#include <libavutil/version.h>
#include <libavutil/imgutils.h>
#include <libavutil/dict.h>
}

#include "ffmpeg_utils.h"
#include <QFileInfo>
#include <QDebug>
#include <QBuffer>

// AudioInfo getAudioInfo(const QString &filePath)
// {
//     AudioInfo info;
//     info.durationSec = 0;
//     info.durationStr = "00:00";
//     info.bitrateKbps = 0;
//     info.sampleRate = 0;
//     info.channels = 0;
//     info.format = "未知";
//     info.codec  = "未知";

//     AVFormatContext *fmtCtx = nullptr;

//     if (avformat_open_input(&fmtCtx, filePath.toUtf8().constData(), nullptr, nullptr) < 0) {
//         qWarning() << "无法打开文件:" << filePath;
//         return info;
//     }

//     if (avformat_find_stream_info(fmtCtx, nullptr) < 0) {
//         qWarning() << "无法获取流信息";
//         avformat_close_input(&fmtCtx);
//         return info;
//     }

//     // 格式 / 容器
//     if (fmtCtx->iformat && fmtCtx->iformat->long_name)
//         info.format = fmtCtx->iformat->long_name;
//     else
//         info.format = "未知";

//     // 默认取第一个音频流
//     int audioStreamIndex = -1;
//     for (unsigned i = 0; i < fmtCtx->nb_streams; i++) {
//         if (fmtCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
//             audioStreamIndex = i;
//             break;
//         }
//     }

//     if (audioStreamIndex >= 0) {
//         AVStream *stream = fmtCtx->streams[audioStreamIndex];
//         AVCodecParameters *codecpar = stream->codecpar;

//         const AVCodec *codec = avcodec_find_decoder(codecpar->codec_id);
//         if (codec && codec->long_name)
//             info.codec = codec->long_name;
//         else
//             info.codec = "未知";

//         info.sampleRate = codecpar->sample_rate;
//         // 声道数：新旧 API 兼容
//     #if LIBAVUTIL_VERSION_MAJOR >= 58
//         // FFmpeg 6/7：使用 AVChannelLayout
//         if (codecpar->ch_layout.nb_channels > 0)
//             info.channels = codecpar->ch_layout.nb_channels;
//         else
//             info.channels = 0;
//     #else
//         // FFmpeg 4/5：旧字段 channels
//         info.channels = codecpar->channels;
//     #endif
//     }

//     // 时长
//     if (fmtCtx->duration > 0) {
//         info.durationSec = static_cast<int>(fmtCtx->duration / AV_TIME_BASE);
//         int minutes = info.durationSec / 60;
//         int seconds = info.durationSec % 60;
//         info.durationStr = QString("%1:%2")
//                                .arg(minutes, 2, 10, QChar('0'))
//                                .arg(seconds, 2, 10, QChar('0'));
//     }

//     // 比特率
//     if (fmtCtx->bit_rate > 0)
//         info.bitrateKbps = fmtCtx->bit_rate / 1000;

//     avformat_close_input(&fmtCtx);
//     return info;
// }


AudioInfo getAudioInfo(const QString& filePath) {
    AudioInfo info;

    // 初始化FFmpeg
    avformat_network_init();

    AVFormatContext* formatContext = avformat_alloc_context();
    if (!formatContext) {
        qDebug() << "Failed to allocate format context";
        return info;
    }

    // 打开音频文件
    if (avformat_open_input(&formatContext, filePath.toUtf8().constData(), nullptr, nullptr) != 0) {
        qDebug() << "Failed to open input file";
        avformat_free_context(formatContext);
        return info;
    }

    // 获取流信息
    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        qDebug() << "Failed to find stream info";
        avformat_close_input(&formatContext);
        return info;
    }

    // 获取元数据
    AVDictionaryEntry* tag = nullptr;
    info.hasCover = false;
    info.hasLyrics = false;
    info.lyrics = "";
    while ((tag = av_dict_get(formatContext->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
        QString key = QString(tag->key).toLower();
        QString value = QString::fromUtf8(tag->value);

        if (key == "artist") {
            info.artist = value;
        } else if (key == "title") {
            info.title = value;
        } else if (key == "album") {
            info.album = value;
        }

        // 检查是否有封面
        for (int i = 0; i < formatContext->nb_streams; i++) {
            if (formatContext->streams[i]->disposition & AV_DISPOSITION_ATTACHED_PIC) {
                info.hasCover = true;
                break;
            }

            // 检查流类型
            if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                info.hasCover = true;
                break;
            }
        }

         // 检查是否有内嵌歌词
        if (key.contains("lyric") || key == "lyrics" || key == "unsyncedlyrics") {
            info.hasLyrics = true;
            break;
        }
    }


    // 如果没有找到，检查所有流
    if (!info.hasLyrics) {
        for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
            AVStream* stream = formatContext->streams[i];
            if (stream->metadata) {
                tag = nullptr;
                while ((tag = av_dict_get(stream->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
                    QString key = QString(tag->key).toLower();
                    if (key.contains("lyric") || key == "lyrics" || key == "unsyncedlyrics") {
                        info.hasLyrics = true;
                        break;
                    }
                }
            }
            if (info.hasLyrics) break;
        }
    }

    // 获取音频流信息
    int audioStreamIndex = -1;
    for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
        if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            audioStreamIndex = i;
            break;
        }
    }

    if (audioStreamIndex != -1) {
        // 获取时长
        int64_t duration = formatContext->duration;
        double durationInSeconds = (double)duration / AV_TIME_BASE;
        QTime time(0,0);
        time = time.addSecs(static_cast<int>(durationInSeconds));
        info.durationStr = time.toString("mm:ss");

        // 获取格式
        info.format = QString(formatContext->iformat->name);

        // 获取音频流参数
        AVCodecParameters* codecParams = formatContext->streams[audioStreamIndex]->codecpar;

        // 采样率
        info.sampleRate = codecParams->sample_rate;

        // 比特率（转换为kbps）
        info.bitrateKbps = formatContext->bit_rate / 1000;

        // 声道数
        if (codecParams->ch_layout.nb_channels > 0)
            info.channels = codecParams->ch_layout.nb_channels;
        else
            info.channels = 0;
    }




    // 清理资源
    avformat_close_input(&formatContext);

    return info;
}

//提取歌曲封面
QImage extractAlbumCover(const QString& filePath) {
    avformat_network_init();

    AVFormatContext* formatContext = avformat_alloc_context();
    if (!formatContext) {
        qDebug() << "Failed to allocate format context";
        return QImage();
    }

    // 打开音频文件
    if (avformat_open_input(&formatContext, filePath.toUtf8().constData(), nullptr, nullptr) != 0) {
        qDebug() << "Failed to open input file";
        avformat_free_context(formatContext);
        return QImage();
    }

    // 获取流信息
    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        qDebug() << "Failed to find stream info";
        avformat_close_input(&formatContext);
        return QImage();
    }

    QImage coverImage;

    // 查找封面（附加图片流）
    for (int i = 0; i < formatContext->nb_streams; i++) {
        AVStream* stream = formatContext->streams[i];

        // 检查是否是附加图片流
        if (stream->disposition & AV_DISPOSITION_ATTACHED_PIC) {
            AVPacket pkt = stream->attached_pic;

            // 将封面数据转换为QImage
            coverImage = QImage::fromData((uchar*)pkt.data, pkt.size);

            if (!coverImage.isNull()) {
                break;
            }
        }

    }
    avformat_close_input(&formatContext);

    return coverImage;
}


//提取歌词
QString extractEmbeddedLyrics(const QString& filePath) {
    avformat_network_init();

    AVFormatContext* formatContext = avformat_alloc_context();
    if (!formatContext) {
        qDebug() << "Failed to allocate format context";
        return "";
    }

    // 打开音频文件
    if (avformat_open_input(&formatContext, filePath.toUtf8().constData(), nullptr, nullptr) != 0) {
        qDebug() << "Failed to open input file";
        avformat_free_context(formatContext);
        return "";
    }

    // 获取流信息
    if (avformat_find_stream_info(formatContext, nullptr) < 0) {
        qDebug() << "Failed to find stream info";
        avformat_close_input(&formatContext);
        return "";
    }

    QString lyrics;

    // 查找内嵌歌词元数据
    AVDictionaryEntry* tag = nullptr;
    while ((tag = av_dict_get(formatContext->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
        QString key = QString(tag->key).toLower();
        QString value = QString::fromUtf8(tag->value);

        // 检查常见的歌词元数据键
        if (key.contains("lyric") || key.contains("unsyncedlyric") ||
            key == "lyrics" || key == "lyrics-eng") {
            lyrics = value;
            break;
        }
    }

    // 如果没有找到，尝试检查所有流
    if (lyrics.isEmpty()) {
        for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
            AVStream* stream = formatContext->streams[i];
            if (stream->metadata) {
                tag = nullptr;
                while ((tag = av_dict_get(stream->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
                    QString key = QString(tag->key).toLower();
                    QString value = QString::fromUtf8(tag->value);

                    if (key.contains("lyric") || key == "lyrics" || key == "unsyncedlyrics") {
                        lyrics = value;
                        break;
                    }
                }
            }
            if (!lyrics.isEmpty()) break;
        }
    }

    avformat_close_input(&formatContext);
    return lyrics;
}
