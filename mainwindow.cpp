#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QStandardItemModel"
#include <qsettings.h>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFile>
#include <QIODevice>
#include <QFileDialog>
#include <QTextStream>
#include <QInputDialog>
#include <QApplication>
#include "ffmpeg_utils.h"
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QRandomGenerator>
#include <QDesktopServices>
#include <QPainter>
#include <QtConcurrent/QtConcurrent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 创建播放列表模型
    playlistModel = new QStandardItemModel(this);
    playlistModel->setHorizontalHeaderLabels({"播放列表", "歌曲数目"});
    ui->playlistTreeView->setModel(playlistModel);
    ui->playlistTreeView->header()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->playlistTreeView->header()->setStyleSheet("QHeaderView::section { color: black; }");
    //qDebug() << playlistModel->rowCount();

    // 初始化歌曲模型
    songModel = new QStandardItemModel(this);
    songModel->setHorizontalHeaderLabels({"歌曲名", "歌手", "时长"});
    ui->songTableView->setModel(songModel);

    // 表格样式优化
    ui->songTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 列宽均分
    ui->songTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);       // 表头居中
    ui->songTableView->verticalHeader()->setVisible(false);                            // 隐藏行号

    // 禁止编辑，只允许选择
    ui->songTableView->setEnabled(true);
    ui->songTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->songTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->songTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->songTableView->setFocusPolicy(Qt::StrongFocus);

    // 可选：表格整体风格
    ui->songTableView->setShowGrid(false);             // 去掉网格线，更像播放器
    ui->songTableView->setAlternatingRowColors(true);  // 交替行颜色

    // 加载默认封面
    m_defaultCover = QImage(":/icon/default_cover.png"); // 使用资源文件中的默认封面
    if (m_defaultCover.isNull()) {
        // 如果没有资源文件，创建一个简单的默认封面
        m_defaultCover = QImage(200, 200, QImage::Format_RGB32);
        m_defaultCover.fill(Qt::darkGray);

        QPainter painter(&m_defaultCover);
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 20));
        painter.drawText(m_defaultCover.rect(), Qt::AlignCenter, "No Cover");
    }

    // 显示默认封面
    ui->pictureLabel->setPixmap(QPixmap::fromImage(m_defaultCover));
    ui->pictureLabel->setScaledContents(true);

    //初始化player
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(m_lastVolume); // 默认音量 50%
    ui->playModeButton->setIcon(QIcon(":/icon/sequence.png"));
    ui->playModeButton->setIconSize(QSize(30,30));

    ui->volumeSlider->setRange(0, 100);
    ui->volumeSlider->setValue(static_cast<int>(m_lastVolume * 100));
    ui->volumeButton->setIcon(QIcon(":/icon/volume_unmuted.png"));
    ui->volumeButton->setIconSize(QSize(30,30));
    ui->playSlider->setRange(0, 0); // 播放进度条 初始范围为0，等媒体加载好再设置


    //初始化状态栏
    statusLabel = new QLabel(this);            //左测
    bitrateLabel = new QLabel(this);        // 右侧音频信息
    samplerateLabel = new QLabel(this);
    channelsLabel = new QLabel(this);
    timeLabel = new QLabel(this);

    statusBar()->addWidget(statusLabel);
    statusLabel->setText("就绪");
    statusLabel->setAlignment(Qt::AlignLeft);
    statusBar()->addPermanentWidget(bitrateLabel);
    statusBar()->addPermanentWidget(samplerateLabel);
    statusBar()->addPermanentWidget(channelsLabel);
    statusBar()->addPermanentWidget(timeLabel);

    hookPlayerSignals(); //监听状态/错误/进度

    loadPlaylists();
    // qDebug() << "分之前： " << playlistModel->rowCount();
    // if(playlistModel->rowCount() == 0){
    //     initPlaylistView();
    //     qDebug() << "初始化播放列表";
    // }else{
    //     loadPlaylists();
    // }

    //菜单信号
    connect(ui->actionAddFile, &QAction::triggered, this, &MainWindow::onActionAddFileTriggered);
    connect(ui->actionNewList, &QAction::triggered, this, &MainWindow::onNewPlaylist);
    connect(ui->actionRemoveList, &QAction::triggered, this, &MainWindow::onRemovePlaylist);
    connect(ui->actionRemoveSong, &QAction::triggered, this, &MainWindow::onRemoveSong);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::onExitApp);
    connect(ui->actionTerminate, &QAction::triggered, this, &MainWindow::onTerminatebtnClicked);
    connect(ui->actionStop, &QAction::triggered, this, &MainWindow::onPlaybtnClicked);
    connect(ui->actionLast, &QAction::triggered, this, &MainWindow::onLastbtnClicked);
    connect(ui->actionNext, &QAction::triggered, this, &MainWindow::onNextbtnClicked);

    connect(ui->actionRandomPlay, &QAction::triggered, this, &MainWindow::onRandomPlayClicked);
    connect(ui->actionSquence, &QAction::triggered, this, &MainWindow::setPlayModeSequence);
    connect(ui->actionLoopList, &QAction::triggered, this, &MainWindow::setPlayModeLoop);
    connect(ui->actionLoopSingle, &QAction::triggered, this, &MainWindow::setPlayModeLoopSingle);
    connect(ui->actionShuffle, &QAction::triggered, this, &MainWindow::setPlayModeShuffle);

    ui->actionx0_1->setData(0.1);       // 倍速设置
    ui->actionx0_2->setData(0.2);
    ui->actionx0_5->setData(0.5);
    ui->actionx0_75->setData(0.75);
    ui->actionx1_0->setData(1.0);
    ui->actionx1_25->setData(1.25);
    ui->actionx1_5->setData(1.5);
    ui->actionx2_0->setData(2.0);
    ui->actionx5_0->setData(5.0);
    ui->actionx10_0->setData(10.0);
    connect(ui->actionx0_1, &QAction::triggered, this, &MainWindow::onPlaybackRateChanged);
    connect(ui->actionx0_2, &QAction::triggered, this, &MainWindow::onPlaybackRateChanged);
    connect(ui->actionx0_5, &QAction::triggered, this, &MainWindow::onPlaybackRateChanged);
    connect(ui->actionx0_75, &QAction::triggered, this, &MainWindow::onPlaybackRateChanged);
    connect(ui->actionx1_0, &QAction::triggered, this, &MainWindow::onPlaybackRateChanged);
    connect(ui->actionx1_25, &QAction::triggered, this, &MainWindow::onPlaybackRateChanged);
    connect(ui->actionx1_5, &QAction::triggered, this, &MainWindow::onPlaybackRateChanged);
    connect(ui->actionx2_0, &QAction::triggered, this, &MainWindow::onPlaybackRateChanged);
    connect(ui->actionx5_0, &QAction::triggered, this, &MainWindow::onPlaybackRateChanged);
    connect(ui->actionx10_0, &QAction::triggered, this, &MainWindow::onPlaybackRateChanged);

    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::onAboutClicked);

    connect(ui->playlistTreeView, &QTreeView::clicked, this, &MainWindow::onPlaylistClicked);
    connect(ui->songTableView, &QTableView::clicked,this, &MainWindow::onSongClicked);
    connect(ui->songTableView, &QTableView::doubleClicked,this, &MainWindow::onSongDoubleClicked);


    //playWidget信号
    connect(ui->playButton, &QPushButton::clicked, this, &MainWindow::onPlaybtnClicked);
    connect(ui->lastButton, &QPushButton::clicked, this, &MainWindow::onLastbtnClicked);
    connect(ui->nextButton, &QPushButton::clicked, this, &MainWindow::onNextbtnClicked);
    connect(ui->terminateButton, &QPushButton::clicked, this, &MainWindow::onTerminatebtnClicked);
    connect(ui->playModeButton, &QPushButton::clicked, this, &MainWindow::onPlayModelbtnClicked);
    connect(ui->volumeSlider, &QSlider::valueChanged, this, &MainWindow::onVolumeSliderChanged);
    connect(ui->volumeButton, &QPushButton::clicked, this, &MainWindow::onVolumebtnClicked);
    connect(ui->likeButton, &QPushButton::clicked, this, &MainWindow::onLikebtnClicked);

    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::onDurationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::onPositionChanged);
    // 用户拖动进度条时
    connect(ui->playSlider, &QSlider::sliderMoved, this, &MainWindow::onSliderMoved);
    connect(ui->playSlider, &QSlider::sliderReleased, this, &MainWindow::onSliderReleased);

    // 绑定状态改变信号（保证按钮和状态同步）
    connect(player, &QMediaPlayer::playbackStateChanged,this, [=](QMediaPlayer::PlaybackState state){
        if (state == QMediaPlayer::PlayingState) {
            ui->playButton->setIcon(QIcon(":/icon/pause.png"));  // 显示暂停图标
            ui->playButton->setIconSize(QSize(35,35));
            isPlaying = true;
        } else {
            ui->playButton->setIcon(QIcon(":/icon/play.png"));  // 显示播放图标
            ui->playButton->setIconSize(QSize(35,35));
            isPlaying = false;
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 菜单栏添加文件
void MainWindow::onActionAddFileTriggered()
{
    if (playlistModel->rowCount() == 0) {
        QMessageBox::warning(this, "提示", "请先创建播放列表！");
        return;
    }

    // 选择目标播放列表（可用输入对话框选择）
    QStringList playlistNames;
    for (int i = 0; i < playlistModel->rowCount(); ++i) {
        playlistNames << playlistModel->item(i, 0)->text();
    }
    bool ok;
    QString playlistName = QInputDialog::getItem(
        this, "选择播放列表", "请选择要添加到的播放列表：",
        playlistNames, 0, false, &ok);
    if (!ok || playlistName.isEmpty()) return;

    // 选择歌曲文件
    QStringList files = QFileDialog::getOpenFileNames(
        this, "选择音频文件", QDir::homePath(),
        "音频文件 (*.mp3 *.wav *.flac *.aac);;所有文件 (*.*)");
    if (files.isEmpty()) return;

    // 添加到数据结构
    QVector<SongRow> &rows = m_songsByPlaylist[playlistName];
    for (const QString &file : files) {
        AudioInfo meta = getAudioInfo(file);
        SongRow song;
        //song.title  = QFileInfo(file).baseName(); // 用文件名当歌名

        song.title = meta.title.isEmpty() ? QFileInfo(file).baseName() : meta.title; // 使用元数据中的标题，如果没有则使用文件名

        song.artist = meta.artist.isEmpty() ? "未知" : meta.artist;  // 使用元数据中的艺术家，如果没有则使用"未知"
        song.time   = meta.durationStr;          // 可扩展用 ffmpeg 获取时长
        song.filePath = file; // 保存完整路径

        rows.push_back(song);
    }

    // 如果用户正在浏览该播放列表 → 刷新右侧
    QModelIndex cur = ui->playlistTreeView->currentIndex();
    if (cur.isValid()) {
        QString current = cur.sibling(cur.row(), 0).data().toString();
        if (current == playlistName) {
            loadSongsForPlaylist(playlistName);
        }
    }

    // 更新左侧歌曲数
    for (int i = 0; i < playlistModel->rowCount(); ++i) {
        if (playlistModel->item(i, 0)->text() == playlistName) {
            playlistModel->item(i, 1)->setText(QString::number(rows.size()));
            break;
        }
    }
}

//菜单栏新建播放列表
void MainWindow::onNewPlaylist()
{
    // 弹出输入框
    bool ok = false;
    QString name = QInputDialog::getText(this, "新建播放列表","请输入新播放列表名称：",QLineEdit::Normal, "", &ok);

    if (!ok || name.trimmed().isEmpty()) {
        return; // 用户取消或输入为空
    }

    name = name.trimmed();

    // 检查是否与已有播放列表重复
    for (int i = 0; i < playlistModel->rowCount(); ++i) {
        if (playlistModel->item(i, 0)->text() == name) {
            QMessageBox::warning(this, "错误", "已存在同名的播放列表！");
            return;
        }
    }

    // 添加到 playlistModel
    QList<QStandardItem*> row;
    row << new QStandardItem(name)
        << new QStandardItem("0");  // 初始歌曲数为 0
    for (auto *it : row) {
        it->setTextAlignment(Qt::AlignCenter);
    }
    playlistModel->appendRow(row);

    // 在内存中注册空列表
    m_songsByPlaylist.insert(name, {});

    //QMessageBox::information(this, "成功", QString("已创建新播放列表：%1").arg(name));
}


// 菜单栏移除播放列表
void MainWindow::onRemovePlaylist()
{
    // if (playlistModel->rowCount() == 0) {
    //     QMessageBox::information(this, "提示", "当前没有播放列表可删除");
    //     return;
    // }

    // 内置保护列表
    //QSet<QString> protectedLists = {""};
    QSet<QString> protectedLists = {"默认列表", "我的收藏", "最近播放"};

    // 收集所有可删除的播放列表
    QStringList deletable;
    for (int i = 0; i < playlistModel->rowCount(); ++i) {
        QString name = playlistModel->item(i, 0)->text();
        if (!protectedLists.contains(name)) {
            deletable << name;
        }
    }

    if (deletable.isEmpty()) {
        QMessageBox::information(this, "提示", "没有可删除的播放列表（内置列表不可删除）");
        return;
    }

    // 弹窗选择
    bool ok = false;
    QString chosen = QInputDialog::getItem(this, "移除播放列表", "选择要移除的列表：", deletable, 0, false, &ok);
    if (!ok || chosen.isEmpty()) return;

    // 删除模型中的对应行
    for (int i = 0; i < playlistModel->rowCount(); ++i) {
        if (playlistModel->item(i, 0)->text() == chosen) {
            playlistModel->removeRow(i);
            break;
        }
    }

    // 删除内存中的数据
    m_songsByPlaylist.remove(chosen);

    // 清空右侧歌曲视图（如果删除的是当前正在显示的）
    if (ui->songTableView->model()->rowCount() > 0) {
        songModel->removeRows(0, songModel->rowCount());
    }

    //QMessageBox::information(this, "提示", QString("已删除播放列表：%1").arg(chosen));
}


// 菜单栏移除歌曲
void MainWindow::onRemoveSong()
{
    QModelIndex currentListIndex = ui->playlistTreeView->currentIndex();
    if (!currentListIndex.isValid()) {
        QMessageBox::warning(this, "提示", "请先选中一个播放列表");
        return;
    }

    // 选择目标播放列表（可用输入对话框选择）
    QStringList playlistNames;
    for (int i = 0; i < playlistModel->rowCount(); ++i) {
        playlistNames << playlistModel->item(i, 0)->text();
    }
    bool ok1;
    QString playlistName = QInputDialog::getItem(
        this, "选择播放列表", "请选择播发列表：",
        playlistNames, 0, false, &ok1);
    if (!ok1 || playlistName.isEmpty()) return;

    //QString playlistName = playlistModel->item(currentListIndex.row(), 0)->text();
    if (!m_songsByPlaylist.contains(playlistName) || m_songsByPlaylist[playlistName].isEmpty()) {
        QMessageBox::information(this, "提示", "该播放列表中没有歌曲");
        return;
    }

    // 收集歌曲名
    QStringList songs;
    for (const auto &s : m_songsByPlaylist[playlistName]) {
        songs << s.title;
    }

    // 弹窗选择
    bool ok2 = false;
    QString chosen = QInputDialog::getItem(this, "移除歌曲", "选择要移除的歌曲：", songs, 0, false, &ok2);
    if (!ok2 || chosen.isEmpty()) return;

    // 找到对应歌曲并移除
    auto &rows = m_songsByPlaylist[playlistName];
    for (int i = 0; i < rows.size(); ++i) {
        if (rows[i].title == chosen) {
            rows.remove(i);
            songModel->removeRow(i);
            break;
        }
    }

    // 更新左侧歌曲数目
    for (int i = 0; i < playlistModel->rowCount(); ++i) {
        if (playlistModel->item(i, 0)->text() == playlistName) {
            playlistModel->item(i, 1)->setText(QString::number(rows.size()));
            break;
        }
    }

    QMessageBox::information(this, "提示", QString("已从 %1 移除歌曲：%2").arg(playlistName, chosen));
}

//菜单栏退出
void MainWindow::onExitApp()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
        this,
        tr("确认退出"),
        tr("是否退出并保存播放列表？"),
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}

//菜单栏随机播放
void MainWindow::onRandomPlayClicked()
{
    QString playlistToUse = m_currentPlaylist;

    // 如果当前没有播放列表，就随机选一个非空列表
    if (playlistToUse.isEmpty() || !m_songsByPlaylist.contains(playlistToUse)) {
        // 找出所有非空播放列表
        QStringList nonEmptyPlaylists;
        for (auto it = m_songsByPlaylist.constBegin(); it != m_songsByPlaylist.constEnd(); ++it) {
            if (!it.value().isEmpty())
                nonEmptyPlaylists << it.key();
        }

        if (nonEmptyPlaylists.isEmpty()) {
            statusBar()->showMessage("没有可用的播放列表（所有播放列表均为空）");
            return;
        }

        // 随机挑选一个非空播放列表
        int pIndex = QRandomGenerator::global()->bounded(nonEmptyPlaylists.size());
        playlistToUse = nonEmptyPlaylists[pIndex];
        m_currentPlaylist = playlistToUse;
    }

    const auto &songs = m_songsByPlaylist[m_currentPlaylist];
    if (songs.isEmpty()) {
        statusBar()->showMessage("该播放列表中没有歌曲");
        return;
    }

    // 收集所有有效路径的索引
    QVector<int> validIndexes;
    for (int i = 0; i < songs.size(); ++i) {
        if (!songs[i].filePath.isEmpty() && QFile::exists(songs[i].filePath)) {
            validIndexes.append(i);
        }
    }

    if (validIndexes.isEmpty()) {
        statusBar()->showMessage("该播放列表中所有歌曲路径均无效");
        return;
    }

    // 从有效索引中随机挑选一个
    int randomIndex = validIndexes[QRandomGenerator::global()->bounded(validIndexes.size())];

    // 更新当前播放信息
    m_currentRow = randomIndex;

    // 播放选中的歌曲
    selectAndPlaySong(m_currentPlaylist, m_currentRow);
}

//菜单栏调整播放速度
void MainWindow::onPlaybackRateChanged()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if (!action || !player) return;

    double rate = action->data().toDouble();
    player->setPlaybackRate(rate);

    statusBar()->showMessage(QString("播放速度：%1x").arg(rate), 5000);
}

// 菜单栏处理"关于"动作
void MainWindow::onAboutClicked()
{
    // 获取应用程序根目录
    QString appDir = QCoreApplication::applicationDirPath();
    QString readmePath = QDir(appDir).filePath("ReadMe.md");

    // 检查文件是否存在
    if (!QFile::exists(readmePath)) {
        QMessageBox::warning(this, "关于",
                             QString("找不到 ReadMe.md 文件\n路径: %1").arg(readmePath));
        return;
    }

    // 使用系统默认程序打开文件
    QUrl fileUrl = QUrl::fromLocalFile(readmePath);
    bool success = QDesktopServices::openUrl(fileUrl);


    if (!success) {
        QMessageBox::warning(this, "关于",
                             "无法打开 ReadMe.md 文件\n请确保系统有关联的应用程序可以打开 .md 文件");
    }
}

//初始化播放列表
void MainWindow::initPlaylistView()
{

    //ui->playlistTreeView->setSelectionBehavior(QAbstractItemView::SelectRows);

    QList<QList<QStandardItem*>> playLists = {
        { new QStandardItem("默认列表"), new QStandardItem("0") },
        { new QStandardItem("我的收藏"), new QStandardItem("0") },
        { new QStandardItem("最近播放"), new QStandardItem("0") }
    };
    //ui->playlistTreeView->header()->setSectionResizeMode(QHeaderView::Stretch);


    for(auto &list : playLists){
        for(auto *it: list){
            it->setTextAlignment(Qt::AlignCenter);
        }
        playlistModel->appendRow(list);
    }
    qDebug() << playlistModel->rowCount();

}

// void MainWindow::onPlaylistClicked(const QModelIndex &index){
//     if (!index.isValid()) return;
//     // 获取点击的行和列
//     int row = index.row();
//     int col = index.column();
//     // 根据需要可以获取播放列表名称
//     QString playlistName = index.sibling(row, 0).data().toString();
//     qDebug() << "用户点击了播放列表:" << playlistName;
//     // 切换到 listPage
//     ui->stackedWidget->setCurrentWidget(ui->listPage);
//     // TODO: 在这里加载该播放列表的歌曲数据到 listPage
//     // 加载歌曲
//     loadSongsForPlaylist(playlistName);
// }

void MainWindow::onPlaylistClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;
    const QString name = index.sibling(index.row(), 0).data().toString();

    loadSongsForPlaylist(name);
    ui->stackedWidget->setCurrentWidget(ui->listPage);
}

void MainWindow::loadSongsForPlaylist(const QString &name)
{
    songModel->removeRows(0, songModel->rowCount()); // 防止叠加

    const auto rows = m_songsByPlaylist.value(name);

    for (const auto &r : rows) {
        auto *titleItem  = new QStandardItem(r.title);
        auto *artistItem = new QStandardItem(r.artist);
        auto *timeItem   = new QStandardItem(r.time);

        // 关键：确保可选、可用（不编辑）
        //const auto flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
        // titleItem->setFlags(flags);
        // artistItem->setFlags(flags);
        // timeItem->setFlags(flags);
        titleItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        artistItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        timeItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        // 可选：居中
        titleItem->setTextAlignment(Qt::AlignCenter);
        artistItem->setTextAlignment(Qt::AlignCenter);
        timeItem->setTextAlignment(Qt::AlignCenter);

        songModel->appendRow(QList<QStandardItem*>{titleItem, artistItem, timeItem});
    }

    // for (const auto &r : rows) {
    //     QList<QStandardItem*> srow;
    //     srow << new QStandardItem(r.title)
    //          << new QStandardItem(r.artist)
    //          << new QStandardItem(r.time);
    //     for (auto *it : srow) it->setTextAlignment(Qt::AlignCenter);
    //     songModel->appendRow(srow);
    // }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    savePlaylists();  // 在窗口关闭前保存播放列表
    event->accept();  // 接受关闭事件
}


void MainWindow::onPlaybtnClicked()
{
    qDebug() << "Play button clicked";
    // TODO: 调用播放器核心逻辑
    if (!player) return;

    if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->pause();
    } else {
        player->play();
    }
}

void MainWindow::onLastbtnClicked()
{
    qDebug() << "Last button clicked";
    // TODO: 调用上一曲核心逻辑
    auto &songs = m_songsByPlaylist[m_currentPlaylist];
    int prevRow = (m_currentRow > 0) ? m_currentRow - 1 : songs.size() - 1;
    selectAndPlaySong(m_currentPlaylist, prevRow);
}

void MainWindow::onNextbtnClicked()
{
    qDebug() << "Next button clicked";
    // TODO: 调用下一曲核心逻辑
    auto &songs = m_songsByPlaylist[m_currentPlaylist];
    int nextRow = (m_currentRow < songs.size()-1) ? m_currentRow + 1 : 0;
    selectAndPlaySong(m_currentPlaylist, nextRow);
}

void MainWindow::onTerminatebtnClicked()
{
    qDebug() << "Terminate button clicked";
    // TODO: 调用播放器核心逻辑
    if (!player) return;

    player->stop();
    m_currentRow = -1;
    isPlaying = false;

    statusBar()->showMessage("播放已终止");
}

void MainWindow::onOutloadbtnClicked()
{
    qDebug() << "Outload button clicked";
    // TODO: 调用播放器核心逻辑
}

void MainWindow::onLikebtnClicked()
{
    qDebug() << "Like button clicked";
    // TODO: 调用播放器核心逻辑
    if (m_currentPlaylist.isEmpty() || m_currentRow < 0) {
        statusBar()->showMessage("当前没有正在播放的歌曲", 5000);
        return;
    }

    const SongRow &currentSong = m_songsByPlaylist[m_currentPlaylist][m_currentRow];
    QString favList = "我的收藏";

    auto &favSongs = m_songsByPlaylist[favList];

    // 查找是否已存在
    auto it = std::find_if(favSongs.begin(), favSongs.end(), [&](const SongRow &s){
        return s.filePath == currentSong.filePath;
    });

    if (it == favSongs.end()) {
        // 不存在 → 添加
        favSongs.push_back(currentSong);
        ui->likeButton->setIcon(QIcon(":/icon/liked.png"));
        ui->likeButton->setIconSize(QSize(30,30));
        statusBar()->showMessage("已添加到『我的收藏』", 5000);
    } else {
        // 已存在 → 移除
        favSongs.erase(it);
        ui->likeButton->setIcon(QIcon(":/icon/like.png"));
        ui->likeButton->setIconSize(QSize(30,30));
        statusBar()->showMessage("已从『我的收藏』移除", 5000);
    }

    // 更新左侧“我的收藏”歌曲数目
    for (int i = 0; i < playlistModel->rowCount(); ++i) {
        if (playlistModel->item(i, 0)->text() == favList) {
            playlistModel->item(i, 1)->setText(QString::number(favSongs.size()));
            break;
        }
    }
}

void MainWindow::onPlayModelbtnClicked()
{
    qDebug() << "PlayModel button clicked";
    // TODO: 调用播放器核心逻辑
    switch (m_playMode) {
    case Sequence:
        setPlayModeLoop();
        break;
    case Loop:
        setPlayModeLoopSingle();
        break;
    case SingleLoop:
        setPlayModeShuffle();
        break;
    case Shuffle:
        setPlayModeSequence();
        break;
    }
    ui->playModeButton->setIconSize(QSize(30,30));
}

void MainWindow::setPlayModeSequence(){
    m_playMode = Sequence;
    ui->playModeButton->setIcon(QIcon(":/icon/sequence.png"));
    //statusBar()->showMessage("播放模式：顺序播放");
    qDebug() << "播放模式：顺序播放";
}

void MainWindow::setPlayModeLoop()
{
    m_playMode = Loop;
    ui->playModeButton->setIcon(QIcon(":/icon/loop.png"));
    //statusBar()->showMessage("播放模式：列表循环");
    qDebug() << "播放模式：列表循环";
}

void MainWindow::setPlayModeLoopSingle()
{
    m_playMode = SingleLoop;
    ui->playModeButton->setIcon(QIcon(":/icon/loop_single.png"));
    //statusBar()->showMessage("播放模式：单曲循环");
    qDebug() << "播放模式：单曲循环";
}

void MainWindow::setPlayModeShuffle()
{
    m_playMode = Shuffle;
    ui->playModeButton->setIcon(QIcon(":/icon/shuffle.png"));
    qDebug() << "播放模式：随机播放";
}

void MainWindow::onVolumeSliderChanged(int value)
{
    qreal vol = value / 100.0;   // Qt6 音量范围 0.0~1.0
    audioOutput->setVolume(vol);

    if (value == 0) {
        m_isMuted = true;
        ui->volumeButton->setIcon(QIcon(":/icon/volume_muted.png"));
    } else {
        m_isMuted = false;
        ui->volumeButton->setIcon(QIcon(":/icon/volume_unmuted.png"));
        m_lastVolume = vol;
    }
    ui->volumeButton->setIconSize(QSize(30,30));
}

void MainWindow::onVolumebtnClicked()
{
    qDebug() << "Volume button clicked";
    // TODO: 调用播放器核心逻辑
    if (!m_isMuted) {
        // 静音
        m_lastVolume = audioOutput->volume();
        ui->volumeSlider->setValue(0);   // 自动触发 onVolumeSliderChanged
    } else {
        // 恢复音量
        ui->volumeSlider->setValue(static_cast<int>(m_lastVolume * 100));
    }

}

void MainWindow::onDurationChanged(qint64 duration)
{
    ui->playSlider->setRange(0, duration);

    // 格式化时间
    QTime totalTime(0,0);
    totalTime = totalTime.addMSecs(duration);
    ui->totaltimeLabel->setText(totalTime.toString("mm:ss"));
}

void MainWindow::onPositionChanged(qint64 pos)
{
    if (!ui->playSlider->isSliderDown()) {
        ui->playSlider->setValue(pos);
    }

    QTime currentTime(0,0);
    currentTime = currentTime.addMSecs(pos);
    ui->playtimeLabel->setText(currentTime.toString("mm:ss"));
}

void MainWindow::onSliderMoved(int value)
{
    QTime currentTime(0,0);
    currentTime = currentTime.addMSecs(value);
    ui->playtimeLabel->setText(currentTime.toString("mm:ss"));  // 拖动时预览
}

void MainWindow::onSliderReleased()
{
    player->setPosition(ui->playSlider->value());
}



void MainWindow::onSongClicked(const QModelIndex &index)
{
    qDebug() << "SongClicked";
    if (!index.isValid()) return;

    int row = index.row();
    QString playlistName = ui->playlistTreeView->currentIndex().siblingAtColumn(0).data().toString();

    if (!m_songsByPlaylist.contains(playlistName)) return;
    const auto &songs = m_songsByPlaylist[playlistName];
    if (row < 0 || row >= songs.size()) return;

    const SongRow &song = songs[row];

    qDebug() << "filePath:" << song.filePath;

    // 调用 FFmpeg 获取更多信息
    AudioInfo meta = getAudioInfo(song.filePath);

    // 更新 infoWidget 各个标签
    ui->TitleLabel->setText("标题：" + song.title);
    ui->ArtistLabel->setText("艺术家：" + song.artist);
    ui->timeLabel->setText("时长：" + meta.durationStr);
    ui->formatLabel->setText("格式：" + meta.format);
    ui->SetLabel->setText("采样率：" + QString::number(meta.sampleRate));

    // 更新专辑封面
    ui->NameLabel->setText(song.title);
    loadAlbumCover(songs[row].filePath);
}

void MainWindow::onSongDoubleClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    int row = index.row();
    QString playlistName = ui->playlistTreeView->currentIndex()
                               .siblingAtColumn(0).data().toString();

    if (!m_songsByPlaylist.contains(playlistName)) return;
    const auto &songs = m_songsByPlaylist[playlistName];
    if (row < 0 || row >= songs.size()) return;

    const SongRow &song = songs[row];
    AudioInfo meta = getAudioInfo(song.filePath);

    // ====== 更新 StatusBar ======
    //statusBar()->showMessage("正在播放：" + songs[row].title + "  ");
    bitrateLabel->setText(QString("%1 kbps").arg(meta.bitrateKbps));
    samplerateLabel->setText(QString("%1 Hz").arg(meta.sampleRate));
    channelsLabel->setText(QString("声道数 %1").arg(meta.channels));
    //timeLabel->setText(QString("%1 / %2").arg("00:00").arg(meta.durationStr));
    connect(player, &QMediaPlayer::positionChanged, this, [=](qint64 pos) {
        QString cur = QTime::fromMSecsSinceStartOfDay(pos).toString("mm:ss");
        timeLabel->setText(QString("%1 / %2").arg(cur, meta.durationStr));
    });

    // TODO: 播放逻辑
    selectAndPlaySong(playlistName, row);

}

//保存播放列表到 QSettings
void MainWindow::savePlaylists()
{
    //QSettings settings("MyCompany", "AudioPlayer");
    //将播放列表和歌曲文件存储到运行目录下的.ini文件中
    QSettings settings(QCoreApplication::applicationDirPath() + "/config.ini",
                       QSettings::IniFormat);

    // 清理旧数据
    settings.remove("Playlists");

    // 用数组写法，避免 childGroups 带来的索引空洞问题
    settings.beginWriteArray("Playlists", playlistModel->rowCount());
    for (int i = 0; i < playlistModel->rowCount(); ++i) {
        settings.setArrayIndex(i);

        const QString name = playlistModel->item(i, 0)->text();
        settings.setValue("Name", name);

        // 取出该播放列表自己的歌曲集合（不再用 songModel！）
        const auto rows = m_songsByPlaylist.value(name);
        settings.beginWriteArray("Songs", rows.size());
        for (int j = 0; j < rows.size(); ++j) {
            settings.setArrayIndex(j);
            settings.setValue("Title",  rows[j].title);
            settings.setValue("Artist", rows[j].artist);
            settings.setValue("Time",   rows[j].time);
            settings.setValue("filePath", rows[j].filePath);
        }
        settings.endArray(); // Songs
    }
    settings.endArray(); // Playlists

    // 保存最近播放列表
    settings.beginWriteArray("RecentlyPlayed", m_recentlyPlayed.size());
    for (int i = 0; i < m_recentlyPlayed.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("FilePath", m_recentlyPlayed[i].first);
        settings.setValue("PlayTime", m_recentlyPlayed[i].second);
    }
    settings.endArray(); // RecentlyPlayed

}


//加载播放列表
void MainWindow::loadPlaylists()
{
    // 清空内存与模型
    m_songsByPlaylist.clear();
    playlistModel->removeRows(0, playlistModel->rowCount());
    songModel->removeRows(0, songModel->rowCount());

    //QSettings settings("MyCompany", "AudioPlayer");
    QSettings settings(QCoreApplication::applicationDirPath() + "/config.ini",
                       QSettings::IniFormat);

    // 先读取 Playlists 数量（用这个值判断是否需要初始化）
    const int n = settings.beginReadArray("Playlists");
    qDebug() << "Playlists count from settings:" << n;

    if (n == 0) {
        // 没有保存的播放列表 —— 初始化默认列表并返回
        initPlaylistView();
        qDebug() << "初始化播放列表 (no saved playlists)";
        settings.endArray();
        return;
    }

    for (int i = 0; i < n; ++i) {
        settings.setArrayIndex(i);

        const QString name = settings.value("Name").toString();

        // 读取该播放列表的歌曲到内存映射（不立即显示到 songModel）
        QVector<SongRow> rows;
        const int m = settings.beginReadArray("Songs");
        rows.reserve(m);
        for (int j = 0; j < m; ++j) {
            settings.setArrayIndex(j);
            rows.push_back(SongRow{
                settings.value("Title").toString(),
                settings.value("Artist").toString(),
                settings.value("Time").toString(),
                settings.value(("filePath")).toString()
            });
        }
        settings.endArray(); // Songs
        m_songsByPlaylist.insert(name, std::move(rows));

        // 左侧只追加播放列表 + 歌曲数
        QList<QStandardItem*> prow;
        prow << new QStandardItem(name)
             << new QStandardItem(QString::number(m));
        for (auto *it : prow) it->setTextAlignment(Qt::AlignCenter);
        playlistModel->appendRow(prow);
    }
    settings.endArray(); // Playlists

    // 加载最近播放列表
    m_recentlyPlayed.clear();
    const int r = settings.beginReadArray("RecentlyPlayed");
    for (int i = 0; i < r; ++i) {
        settings.setArrayIndex(i);
        QString filePath = settings.value("FilePath").toString();
        QDateTime playTime = settings.value("PlayTime").toDateTime();

        // 检查文件是否仍然存在
        if (QFile::exists(filePath)) {
            m_recentlyPlayed.append(qMakePair(filePath, playTime));
        }
    }
    settings.endArray(); // RecentlyPlayed

    // 更新最近播放列表
    updateRecentPlaylist();

    // 可选：默认选中第 0 个列表并加载其歌曲到右侧
    if (playlistModel->rowCount() > 0) {
        const QString first = playlistModel->item(0, 0)->text();
        loadSongsForPlaylist(first);             // 只加载一个，不会重复
        ui->playlistTreeView->setCurrentIndex(playlistModel->index(0, 0));
        ui->stackedWidget->setCurrentWidget(ui->listPage);
    }
}

void MainWindow::selectAndPlaySong(const QString &playlistName, int row)
{
    if (!m_songsByPlaylist.contains(playlistName)) return;
    auto &songs = m_songsByPlaylist[playlistName];
    if (row < 0 || row >= songs.size()) return;

    // 更新最近播放列表
    updateRecentlyPlayed(songs[row].filePath);

    // 更新当前播放状态
    m_currentPlaylist = playlistName;
    m_currentRow = row;

    // 更新 likeButton 图标
    auto &favSongs = m_songsByPlaylist["我的收藏"];
    bool liked = std::any_of(favSongs.begin(), favSongs.end(), [&](const SongRow &s){
        return s.filePath == songs[row].filePath;
    });
    if (liked) {
        ui->likeButton->setIcon(QIcon(":/icon/liked.png"));
    } else {
        ui->likeButton->setIcon(QIcon(":/icon/like.png"));
    }
    ui->likeButton->setIconSize(QSize(30,30));

    // 加载专辑封面
    loadAlbumCover(songs[row].filePath);

    // 播放
    playSong(songs[row].filePath);
    statusLabel->setText("正在播放：" + songs[row].title + "  来自播放列表:" + playlistName);
    qDebug() << "正在播放歌曲:" << songs[row].title << "来自播放列表:" << playlistName;

    // 高亮
    highlightCurrentRow();
}

void MainWindow::playSong(const QString &filePath)
{
    if (filePath.isEmpty()) return;

    player->setSource(QUrl::fromLocalFile(filePath));
    player->play();
    isPlaying = true;

    qDebug() << "开始播放:" << filePath;
}

void MainWindow::highlightCurrentRow()
{
    if (m_currentRow < 0) return;
    const auto idx = songModel->index(m_currentRow, 0);
    if (!idx.isValid()) return;
    ui->songTableView->setCurrentIndex(idx);
}

void MainWindow::hookPlayerSignals()
{
    connect(player, &QMediaPlayer::errorOccurred, this, [this](QMediaPlayer::Error err){
        if (err != QMediaPlayer::NoError)
            statusBar()->showMessage("播放出错");
    });
    connect(player, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus st){
        if (st == QMediaPlayer::EndOfMedia) {
            // TODO: 自动下一首
            const auto &songs = m_songsByPlaylist[m_currentPlaylist];
            switch (m_playMode) {
            case Sequence:
                if(m_currentRow == songs.size()-1){
                    onTerminatebtnClicked();
                }else{
                    selectAndPlaySong(m_currentPlaylist, m_currentRow + 1);
                }
                break;
            case Loop:
                onNextbtnClicked();
                break;
            case SingleLoop:
                selectAndPlaySong(m_currentPlaylist, m_currentRow);
                break;
            case Shuffle:
                onRandomPlayClicked();
                break;
            }
        }
    });
}


// 更新最近播放的歌曲
void MainWindow::updateRecentlyPlayed(const QString &filePath)
{
    if (filePath.isEmpty()) return;

    QDateTime currentTime = QDateTime::currentDateTime();

    // 检查是否已经存在于最近播放列表中
    for (int i = 0; i < m_recentlyPlayed.size(); ++i) {
        if (m_recentlyPlayed[i].first == filePath) {
            // 如果存在，更新播放时间并移到最前面
            m_recentlyPlayed.move(i, 0);
            m_recentlyPlayed[0].second = currentTime;
            return;
        }
    }

    // 如果不存在，添加到最前面
    m_recentlyPlayed.prepend(qMakePair(filePath, currentTime));

    // 如果超过最大限制，删除最早的记录
    if (m_recentlyPlayed.size() > MAX_RECENT_SONGS) {
        m_recentlyPlayed.removeLast();
    }

    // 更新"最近播放"播放列表
    updateRecentPlaylist();
}

// 更新"最近播放"播放列表
void MainWindow::updateRecentPlaylist()
{
    // 获取"最近播放"播放列表的引用
    QVector<SongRow> &recentSongs = m_songsByPlaylist["最近播放"];
    recentSongs.clear();

    // 从最近播放记录中添加歌曲到播放列表
    for (const auto &recent : m_recentlyPlayed) {
        AudioInfo meta = getAudioInfo(recent.first);
        SongRow song;
        song.title = QFileInfo(recent.first).baseName();
        song.artist = "未知";
        song.time = meta.durationStr;
        song.filePath = recent.first;

        recentSongs.append(song);
    }

    // 更新左侧歌曲数目
    for (int i = 0; i < playlistModel->rowCount(); ++i) {
        if (playlistModel->item(i, 0)->text() == "最近播放") {
            playlistModel->item(i, 1)->setText(QString::number(recentSongs.size()));
            break;
        }
    }

    // 如果当前正在显示"最近播放"列表，刷新显示
    QModelIndex currentIndex = ui->playlistTreeView->currentIndex();
    if (currentIndex.isValid()) {
        QString currentPlaylist = currentIndex.sibling(currentIndex.row(), 0).data().toString();
        if (currentPlaylist == "最近播放") {
            loadSongsForPlaylist("最近播放");
        }
    }
}

// 添加加载专辑封面的方法
void MainWindow::loadAlbumCover(const QString& filePath)
{
    if (filePath.isEmpty()) {
        ui->pictureLabel->setPixmap(QPixmap::fromImage(m_defaultCover));
        ui->pictureLabel->setScaledContents(true);
        return;
    }

    // 检查缓存
    if (m_coverCache.contains(filePath)) {
        QImage cover = m_coverCache.value(filePath);
        ui->pictureLabel->setPixmap(QPixmap::fromImage(cover));
        ui->pictureLabel->setScaledContents(true);
        return;
    }

    // 取消相同文件的先前任务（如果存在）
    if (m_coverFutures.contains(filePath)) {
        m_coverFutures[filePath].cancel();
    }

    // 异步加载封面以避免界面冻结
    m_coverFutures[filePath] = QtConcurrent::run([this, filePath]() {
        QImage cover = extractAlbumCover(filePath);

        // 回到主线程更新UI
        QMetaObject::invokeMethod(this, [this, filePath, cover]() {
            if (cover.isNull()) {
                // 如果没有封面，使用默认封面
                ui->pictureLabel->setPixmap(QPixmap::fromImage(m_defaultCover));
                ui->pictureLabel->setScaledContents(true);

                ui->pictureLabel->setScaledContents(false);
            } else {
                // 缩放封面以适应标签大小
                QImage scaledCover = cover.scaled(
                    ui->pictureLabel->width(), ui->pictureLabel->height(),
                    Qt::KeepAspectRatio, Qt::SmoothTransformation);

                // 缓存封面
                m_coverCache.insert(filePath, scaledCover);

                // 显示封面
                ui->pictureLabel->setPixmap(QPixmap::fromImage(scaledCover));
                ui->pictureLabel->setScaledContents(false);
            }
        });
    });
}
