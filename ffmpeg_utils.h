#pragma once
#include <QString>
#include <QMap>
#include <QImage>


struct AudioInfo {
    QString format;     // 格式 / 容器
    QString codec;      // 编码器
    int durationSec;    // 时长（秒）
    QString durationStr; // 格式化 mm:ss
    int bitrateKbps;    // 比特率 kbps
    int sampleRate;     // 采样率 Hz
    int channels;       // 声道数
    QString title;       // 标题
    QString album;       // 专辑
    QString artist;      // 艺术家
    bool hasCover;       // 是否有封面
    bool hasLyrics;      // 是否有内嵌歌词
    QString lyrics;      // 歌词内容
};

AudioInfo getAudioInfo(const QString &filePath);
QImage extractAlbumCover(const QString& filePath);
QString extractEmbeddedLyrics(const QString& filePath);
