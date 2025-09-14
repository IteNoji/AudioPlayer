#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QImage>
#include <QString>
#include <QtConcurrent/QtConcurrent>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
#include <libavformat/version.h>
#include <libavutil/time.h>
#include <libavutil/mathematics.h>
}
#include<QStandardItemModel>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    //菜单
    void onActionAddFileTriggered(); //文件
    void onNewPlaylist();    //新建播放列表
    void onRemovePlaylist(); //移除播放列表
    void onRemoveSong();     //移除歌曲
    void onExitApp();        //退出
    void onRandomPlayClicked(); //随机播放一首
    void onPlaybackRateChanged(); //调整播放速度

    void onPlaylistClicked(const QModelIndex &index);
    void onPlaybtnClicked();
    void onLastbtnClicked();
    void onNextbtnClicked();
    void onOutloadbtnClicked();
    void onLikebtnClicked();
    void onPlayModelbtnClicked();
    void onTerminatebtnClicked();
    void onVolumebtnClicked();
    void onVolumeSliderChanged(int value);

    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 pos);
    void onSliderMoved(int value);
    void onSliderReleased();

    void onAboutClicked(); // 处理"关于"动作


    void onSongClicked(const QModelIndex &index);
    void onSongDoubleClicked(const QModelIndex &index);


private:
    Ui::MainWindow *ui;
    QStandardItemModel *songModel;
    QStandardItemModel *playlistModel;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QLabel *statusLabel;
    QLabel *bitrateLabel;        // 右侧音频信息
    QLabel *samplerateLabel;
    QLabel *channelsLabel;
    QLabel *timeLabel;
    QString m_currentPlaylist;
    int     m_currentRow = -1;
    bool isPlaying = false;
    QHash<QString, QImage> m_coverCache; // 封面缓存
    QImage m_defaultCover;               // 默认封面
    QHash<QString, QFuture<void>> m_coverFutures;  //更新封面线程记录
    // 最近播放列表，存储文件路径和播放时间
    QList<QPair<QString, QDateTime>> m_recentlyPlayed;
    const int MAX_RECENT_SONGS = 50; // 最大记录数

    qreal m_lastVolume = 0.5;   // 记录上次的音量（静音时用来恢复）
    bool m_isMuted = false;  // 静音状态

    void setPlayModeSequence();  // 菜单设置播放模式
    void setPlayModeLoop();
    void setPlayModeLoopSingle();
    void setPlayModeShuffle();

    // 更新最近播放列表
    void updateRecentlyPlayed(const QString &filePath);
    void updateRecentPlaylist();

    // 初始化歌曲模型
    struct SongRow {
        QString title;
        QString artist;
        QString time;
        QString filePath;   // 新增：存储文件路径
    };

    // 初始化播放模式
    enum PlayMode {
        Sequence,
        Loop,
        SingleLoop,
        Shuffle
    };
    PlayMode m_playMode = Sequence;  // 默认顺序播放

    // 每个播放列表名 -> 该列表的歌曲集合
    QHash<QString, QVector<SongRow>> m_songsByPlaylist;



    void initPlaylistView();
    void loadSongsForPlaylist(const QString &playlistName);
    void savePlaylists();
    void loadPlaylists();
    void playSong(const QString &filePath);
    void selectAndPlaySong(const QString &playlistName, int row);
    void highlightCurrentRow();
    void hookPlayerSignals(); // 播放状态/错误等
    void loadAlbumCover(const QString& filePath); // 加载专辑封面

    void closeEvent(QCloseEvent *event);


};
#endif // MAINWINDOW_H
