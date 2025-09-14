/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionNewList;
    QAction *actionAddFile;
    QAction *actionRemoveSong;
    QAction *actionTerminate;
    QAction *actionStop;
    QAction *actionLast;
    QAction *actionNext;
    QAction *actionRandomPlay;
    QAction *actionAbout;
    QAction *actionSquence;
    QAction *actionShuffle;
    QAction *actionLoopSingle;
    QAction *actionLoopList;
    QAction *actionx10_0;
    QAction *actionx5_0;
    QAction *actionx2_0;
    QAction *actionx1_5;
    QAction *actionx1_25;
    QAction *actionx1_0;
    QAction *actionx0_75;
    QAction *actionx0_5;
    QAction *actionx0_2;
    QAction *actionx0_1;
    QAction *actionExit;
    QAction *actionRemoveList;
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout;
    QTreeView *playlistTreeView;
    QWidget *lyricsWidget;
    QGridLayout *gridLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *listPage;
    QGridLayout *gridLayout_5;
    QTableView *songTableView;
    QWidget *lyricsPage;
    QVBoxLayout *verticalLayout;
    QWidget *pictureWidget;
    QGridLayout *gridLayout_3;
    QLabel *pictureLabel;
    QLabel *NameLabel;
    QWidget *infoWidget;
    QGridLayout *gridLayout;
    QLabel *TitleLabel;
    QLabel *SetLabel;
    QLabel *timeLabel;
    QLabel *ArtistLabel;
    QLabel *formatLabel;
    QWidget *playWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *playtimeLabel;
    QSlider *playSlider;
    QLabel *totaltimeLabel;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *playModeButton;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *outloadButton;
    QPushButton *lastButton;
    QPushButton *playButton;
    QPushButton *nextButton;
    QPushButton *terminateButton;
    QPushButton *likeButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *volumeButton;
    QSlider *volumeSlider;
    QSpacerItem *horizontalSpacer_3;
    QMenuBar *menubar;
    QMenu *fileMenu;
    QMenu *playMenu;
    QMenu *menuPlaySpeed;
    QMenu *menuSequence;
    QMenu *helpMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8("icon/Music.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonFollowStyle);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionNewList = new QAction(MainWindow);
        actionNewList->setObjectName("actionNewList");
        actionAddFile = new QAction(MainWindow);
        actionAddFile->setObjectName("actionAddFile");
        actionRemoveSong = new QAction(MainWindow);
        actionRemoveSong->setObjectName("actionRemoveSong");
        actionTerminate = new QAction(MainWindow);
        actionTerminate->setObjectName("actionTerminate");
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName("actionStop");
        actionLast = new QAction(MainWindow);
        actionLast->setObjectName("actionLast");
        actionNext = new QAction(MainWindow);
        actionNext->setObjectName("actionNext");
        actionRandomPlay = new QAction(MainWindow);
        actionRandomPlay->setObjectName("actionRandomPlay");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        actionSquence = new QAction(MainWindow);
        actionSquence->setObjectName("actionSquence");
        actionShuffle = new QAction(MainWindow);
        actionShuffle->setObjectName("actionShuffle");
        actionLoopSingle = new QAction(MainWindow);
        actionLoopSingle->setObjectName("actionLoopSingle");
        actionLoopList = new QAction(MainWindow);
        actionLoopList->setObjectName("actionLoopList");
        actionx10_0 = new QAction(MainWindow);
        actionx10_0->setObjectName("actionx10_0");
        actionx5_0 = new QAction(MainWindow);
        actionx5_0->setObjectName("actionx5_0");
        actionx2_0 = new QAction(MainWindow);
        actionx2_0->setObjectName("actionx2_0");
        actionx1_5 = new QAction(MainWindow);
        actionx1_5->setObjectName("actionx1_5");
        actionx1_25 = new QAction(MainWindow);
        actionx1_25->setObjectName("actionx1_25");
        actionx1_0 = new QAction(MainWindow);
        actionx1_0->setObjectName("actionx1_0");
        actionx0_75 = new QAction(MainWindow);
        actionx0_75->setObjectName("actionx0_75");
        actionx0_5 = new QAction(MainWindow);
        actionx0_5->setObjectName("actionx0_5");
        actionx0_2 = new QAction(MainWindow);
        actionx0_2->setObjectName("actionx0_2");
        actionx0_1 = new QAction(MainWindow);
        actionx0_1->setObjectName("actionx0_1");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionRemoveList = new QAction(MainWindow);
        actionRemoveList->setObjectName("actionRemoveList");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName("horizontalLayout");
        playlistTreeView = new QTreeView(centralwidget);
        playlistTreeView->setObjectName("playlistTreeView");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(playlistTreeView->sizePolicy().hasHeightForWidth());
        playlistTreeView->setSizePolicy(sizePolicy1);
        playlistTreeView->setMinimumSize(QSize(150, 0));
        playlistTreeView->setStyleSheet(QString::fromUtf8("background-color: rgb(64, 64, 64);\n"
"color:white;"));
        playlistTreeView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        playlistTreeView->setAlternatingRowColors(false);
        playlistTreeView->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
        playlistTreeView->setUniformRowHeights(true);
        playlistTreeView->setHeaderHidden(false);
        playlistTreeView->header()->setVisible(true);
        playlistTreeView->header()->setCascadingSectionResizes(false);
        playlistTreeView->header()->setMinimumSectionSize(35);
        playlistTreeView->header()->setDefaultSectionSize(75);

        horizontalLayout->addWidget(playlistTreeView);

        lyricsWidget = new QWidget(centralwidget);
        lyricsWidget->setObjectName("lyricsWidget");
        sizePolicy.setHeightForWidth(lyricsWidget->sizePolicy().hasHeightForWidth());
        lyricsWidget->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(lyricsWidget);
        gridLayout_2->setObjectName("gridLayout_2");
        stackedWidget = new QStackedWidget(lyricsWidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy2);
        stackedWidget->setMouseTracking(false);
        stackedWidget->setTabletTracking(false);
        stackedWidget->setAcceptDrops(false);
        stackedWidget->setAutoFillBackground(false);
        listPage = new QWidget();
        listPage->setObjectName("listPage");
        listPage->setEnabled(true);
        sizePolicy.setHeightForWidth(listPage->sizePolicy().hasHeightForWidth());
        listPage->setSizePolicy(sizePolicy);
        gridLayout_5 = new QGridLayout(listPage);
        gridLayout_5->setSpacing(0);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        songTableView = new QTableView(listPage);
        songTableView->setObjectName("songTableView");
        songTableView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        songTableView->setTabKeyNavigation(false);
        songTableView->setDragDropOverwriteMode(false);
        songTableView->setAlternatingRowColors(true);
        songTableView->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
        songTableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        songTableView->setTextElideMode(Qt::TextElideMode::ElideRight);

        gridLayout_5->addWidget(songTableView, 0, 0, 1, 1);

        stackedWidget->addWidget(listPage);
        lyricsPage = new QWidget();
        lyricsPage->setObjectName("lyricsPage");
        sizePolicy.setHeightForWidth(lyricsPage->sizePolicy().hasHeightForWidth());
        lyricsPage->setSizePolicy(sizePolicy);
        stackedWidget->addWidget(lyricsPage);

        gridLayout_2->addWidget(stackedWidget, 0, 0, 1, 1);


        horizontalLayout->addWidget(lyricsWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName("verticalLayout");
        pictureWidget = new QWidget(centralwidget);
        pictureWidget->setObjectName("pictureWidget");
        sizePolicy1.setHeightForWidth(pictureWidget->sizePolicy().hasHeightForWidth());
        pictureWidget->setSizePolicy(sizePolicy1);
        pictureWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(64,64,64);\n"
"color:white;"));
        gridLayout_3 = new QGridLayout(pictureWidget);
        gridLayout_3->setObjectName("gridLayout_3");
        pictureLabel = new QLabel(pictureWidget);
        pictureLabel->setObjectName("pictureLabel");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pictureLabel->sizePolicy().hasHeightForWidth());
        pictureLabel->setSizePolicy(sizePolicy3);
        pictureLabel->setMinimumSize(QSize(200, 200));
        pictureLabel->setStyleSheet(QString::fromUtf8("border-image:url(:/icon/default_cover.png)"));
        pictureLabel->setScaledContents(true);
        pictureLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_3->addWidget(pictureLabel, 0, 0, 1, 1);

        NameLabel = new QLabel(pictureWidget);
        NameLabel->setObjectName("NameLabel");
        NameLabel->setScaledContents(true);
        NameLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        NameLabel->setWordWrap(true);

        gridLayout_3->addWidget(NameLabel, 1, 0, 1, 1);

        gridLayout_3->setRowStretch(0, 5);
        gridLayout_3->setRowStretch(1, 1);

        verticalLayout->addWidget(pictureWidget);

        infoWidget = new QWidget(centralwidget);
        infoWidget->setObjectName("infoWidget");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(infoWidget->sizePolicy().hasHeightForWidth());
        infoWidget->setSizePolicy(sizePolicy4);
        infoWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(64,64,64);\n"
"color:white;"));
        gridLayout = new QGridLayout(infoWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(-1, 20, -1, 20);
        TitleLabel = new QLabel(infoWidget);
        TitleLabel->setObjectName("TitleLabel");
        TitleLabel->setScaledContents(true);
        TitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        TitleLabel->setWordWrap(true);

        gridLayout->addWidget(TitleLabel, 0, 0, 1, 1);

        SetLabel = new QLabel(infoWidget);
        SetLabel->setObjectName("SetLabel");
        SetLabel->setScaledContents(true);
        SetLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        SetLabel->setWordWrap(true);

        gridLayout->addWidget(SetLabel, 2, 0, 1, 1);

        timeLabel = new QLabel(infoWidget);
        timeLabel->setObjectName("timeLabel");
        timeLabel->setScaledContents(true);
        timeLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        timeLabel->setWordWrap(true);

        gridLayout->addWidget(timeLabel, 3, 0, 1, 1);

        ArtistLabel = new QLabel(infoWidget);
        ArtistLabel->setObjectName("ArtistLabel");
        ArtistLabel->setScaledContents(true);
        ArtistLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        ArtistLabel->setWordWrap(true);

        gridLayout->addWidget(ArtistLabel, 1, 0, 1, 1);

        formatLabel = new QLabel(infoWidget);
        formatLabel->setObjectName("formatLabel");
        formatLabel->setScaledContents(true);
        formatLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        formatLabel->setWordWrap(true);

        gridLayout->addWidget(formatLabel, 4, 0, 1, 1);


        verticalLayout->addWidget(infoWidget);


        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 6);
        horizontalLayout->setStretch(2, 3);

        gridLayout_4->addLayout(horizontalLayout, 0, 0, 1, 1);

        playWidget = new QWidget(centralwidget);
        playWidget->setObjectName("playWidget");
        sizePolicy2.setHeightForWidth(playWidget->sizePolicy().hasHeightForWidth());
        playWidget->setSizePolicy(sizePolicy2);
        playWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        verticalLayout_2 = new QVBoxLayout(playWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(50, -1, 50, -1);
        playtimeLabel = new QLabel(playWidget);
        playtimeLabel->setObjectName("playtimeLabel");

        horizontalLayout_3->addWidget(playtimeLabel);

        playSlider = new QSlider(playWidget);
        playSlider->setObjectName("playSlider");
        playSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_3->addWidget(playSlider);

        totaltimeLabel = new QLabel(playWidget);
        totaltimeLabel->setObjectName("totaltimeLabel");

        horizontalLayout_3->addWidget(totaltimeLabel);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(20);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(50, -1, -1, -1);
        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        playModeButton = new QPushButton(playWidget);
        playModeButton->setObjectName("playModeButton");
        playModeButton->setMinimumSize(QSize(30, 30));
        playModeButton->setMaximumSize(QSize(30, 30));
        playModeButton->setStyleSheet(QString::fromUtf8("border:none;"));

        horizontalLayout_2->addWidget(playModeButton);

        horizontalSpacer_4 = new QSpacerItem(100, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        outloadButton = new QPushButton(playWidget);
        outloadButton->setObjectName("outloadButton");
        sizePolicy1.setHeightForWidth(outloadButton->sizePolicy().hasHeightForWidth());
        outloadButton->setSizePolicy(sizePolicy1);
        outloadButton->setMaximumSize(QSize(30, 30));
        outloadButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icon/outload.png);\n"
"}\n"
"\n"
"QPushButton:hover {\n"
" border-image: url(:/icon/outload.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
" border-image: url(:/icon/outload.png);\n"
"}"));

        horizontalLayout_2->addWidget(outloadButton);

        lastButton = new QPushButton(playWidget);
        lastButton->setObjectName("lastButton");
        sizePolicy1.setHeightForWidth(lastButton->sizePolicy().hasHeightForWidth());
        lastButton->setSizePolicy(sizePolicy1);
        lastButton->setMaximumSize(QSize(30, 30));
        lastButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icon/last.png);\n"
"}\n"
"\n"
"QPushButton:hover {\n"
" border-image: url(:/icon/last.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
" border-image: url(:/icon/last.png);\n"
"}"));

        horizontalLayout_2->addWidget(lastButton);

        playButton = new QPushButton(playWidget);
        playButton->setObjectName("playButton");
        sizePolicy1.setHeightForWidth(playButton->sizePolicy().hasHeightForWidth());
        playButton->setSizePolicy(sizePolicy1);
        playButton->setMinimumSize(QSize(35, 35));
        playButton->setMaximumSize(QSize(35, 35));
        playButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icon/play.png);\n"
"}\n"
"\n"
"QPushButton:hover {\n"
" border-image: url(:/icon/play.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
" border-image: url(:/icon/play.png);\n"
"}"));

        horizontalLayout_2->addWidget(playButton);

        nextButton = new QPushButton(playWidget);
        nextButton->setObjectName("nextButton");
        sizePolicy1.setHeightForWidth(nextButton->sizePolicy().hasHeightForWidth());
        nextButton->setSizePolicy(sizePolicy1);
        nextButton->setMinimumSize(QSize(30, 30));
        nextButton->setMaximumSize(QSize(30, 30));
        nextButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icon/next.png);\n"
"}\n"
"\n"
"QPushButton:hover {\n"
" border-image: url(:/icon/next.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
" border-image: url(:/icon/next.png);\n"
"}"));

        horizontalLayout_2->addWidget(nextButton);

        terminateButton = new QPushButton(playWidget);
        terminateButton->setObjectName("terminateButton");
        sizePolicy1.setHeightForWidth(terminateButton->sizePolicy().hasHeightForWidth());
        terminateButton->setSizePolicy(sizePolicy1);
        terminateButton->setMaximumSize(QSize(20, 20));
        terminateButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icon/terminate.png);\n"
"}\n"
"\n"
"QPushButton:hover {\n"
" border-image: url(:/icon/terminate.png);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
" border-image: url(:/icon/terminate.png);\n"
"}"));

        horizontalLayout_2->addWidget(terminateButton);

        likeButton = new QPushButton(playWidget);
        likeButton->setObjectName("likeButton");
        sizePolicy1.setHeightForWidth(likeButton->sizePolicy().hasHeightForWidth());
        likeButton->setSizePolicy(sizePolicy1);
        likeButton->setMaximumSize(QSize(30, 30));
        likeButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/icon/like.png);\n"
"}\n"
""));

        horizontalLayout_2->addWidget(likeButton);

        horizontalSpacer_2 = new QSpacerItem(30, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        volumeButton = new QPushButton(playWidget);
        volumeButton->setObjectName("volumeButton");
        volumeButton->setMinimumSize(QSize(0, 0));
        volumeButton->setMaximumSize(QSize(30, 30));
        volumeButton->setStyleSheet(QString::fromUtf8("border:none;"));

        horizontalLayout_2->addWidget(volumeButton);

        volumeSlider = new QSlider(playWidget);
        volumeSlider->setObjectName("volumeSlider");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(volumeSlider->sizePolicy().hasHeightForWidth());
        volumeSlider->setSizePolicy(sizePolicy5);
        volumeSlider->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        volumeSlider->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        volumeSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_2->addWidget(volumeSlider);

        horizontalSpacer_3 = new QSpacerItem(30, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_2);


        gridLayout_4->addWidget(playWidget, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(menubar->sizePolicy().hasHeightForWidth());
        menubar->setSizePolicy(sizePolicy6);
        fileMenu = new QMenu(menubar);
        fileMenu->setObjectName("fileMenu");
        sizePolicy2.setHeightForWidth(fileMenu->sizePolicy().hasHeightForWidth());
        fileMenu->setSizePolicy(sizePolicy2);
        playMenu = new QMenu(menubar);
        playMenu->setObjectName("playMenu");
        sizePolicy2.setHeightForWidth(playMenu->sizePolicy().hasHeightForWidth());
        playMenu->setSizePolicy(sizePolicy2);
        menuPlaySpeed = new QMenu(playMenu);
        menuPlaySpeed->setObjectName("menuPlaySpeed");
        menuSequence = new QMenu(playMenu);
        menuSequence->setObjectName("menuSequence");
        helpMenu = new QMenu(menubar);
        helpMenu->setObjectName("helpMenu");
        sizePolicy2.setHeightForWidth(helpMenu->sizePolicy().hasHeightForWidth());
        helpMenu->setSizePolicy(sizePolicy2);
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        QSizePolicy sizePolicy7(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(statusbar->sizePolicy().hasHeightForWidth());
        statusbar->setSizePolicy(sizePolicy7);
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(fileMenu->menuAction());
        menubar->addAction(playMenu->menuAction());
        menubar->addAction(helpMenu->menuAction());
        fileMenu->addAction(actionOpen);
        fileMenu->addAction(actionNewList);
        fileMenu->addAction(actionRemoveList);
        fileMenu->addAction(actionAddFile);
        fileMenu->addAction(actionRemoveSong);
        fileMenu->addAction(actionExit);
        playMenu->addAction(actionTerminate);
        playMenu->addAction(actionStop);
        playMenu->addAction(actionLast);
        playMenu->addAction(actionNext);
        playMenu->addAction(actionRandomPlay);
        playMenu->addAction(menuSequence->menuAction());
        playMenu->addAction(menuPlaySpeed->menuAction());
        menuPlaySpeed->addAction(actionx10_0);
        menuPlaySpeed->addAction(actionx5_0);
        menuPlaySpeed->addAction(actionx2_0);
        menuPlaySpeed->addAction(actionx1_5);
        menuPlaySpeed->addAction(actionx1_25);
        menuPlaySpeed->addAction(actionx1_0);
        menuPlaySpeed->addAction(actionx0_75);
        menuPlaySpeed->addAction(actionx0_5);
        menuPlaySpeed->addAction(actionx0_2);
        menuPlaySpeed->addAction(actionx0_1);
        menuSequence->addAction(actionSquence);
        menuSequence->addAction(actionShuffle);
        menuSequence->addAction(actionLoopSingle);
        menuSequence->addAction(actionLoopList);
        helpMenu->addAction(actionAbout);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
        actionNewList->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\346\222\255\346\224\276\345\210\227\350\241\250", nullptr));
        actionAddFile->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\346\226\207\344\273\266", nullptr));
        actionRemoveSong->setText(QCoreApplication::translate("MainWindow", "\347\247\273\351\231\244\346\226\207\344\273\266", nullptr));
        actionTerminate->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        actionStop->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        actionLast->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\270\200\351\246\226", nullptr));
        actionNext->setText(QCoreApplication::translate("MainWindow", "\344\270\213\344\270\200\351\246\226", nullptr));
        actionRandomPlay->setText(QCoreApplication::translate("MainWindow", "\351\232\217\346\234\272", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
        actionSquence->setText(QCoreApplication::translate("MainWindow", "\351\241\272\345\272\217", nullptr));
        actionShuffle->setText(QCoreApplication::translate("MainWindow", "\351\232\217\346\234\272", nullptr));
        actionLoopSingle->setText(QCoreApplication::translate("MainWindow", "\345\215\225\346\233\262\345\276\252\347\216\257", nullptr));
        actionLoopList->setText(QCoreApplication::translate("MainWindow", "\345\210\227\350\241\250\345\276\252\347\216\257", nullptr));
        actionx10_0->setText(QCoreApplication::translate("MainWindow", "x10.0", nullptr));
        actionx5_0->setText(QCoreApplication::translate("MainWindow", "x5.0", nullptr));
        actionx2_0->setText(QCoreApplication::translate("MainWindow", "x2.0", nullptr));
        actionx1_5->setText(QCoreApplication::translate("MainWindow", "x1.5", nullptr));
        actionx1_25->setText(QCoreApplication::translate("MainWindow", "x1.25", nullptr));
        actionx1_0->setText(QCoreApplication::translate("MainWindow", "x1.0", nullptr));
        actionx0_75->setText(QCoreApplication::translate("MainWindow", "x0.75", nullptr));
        actionx0_5->setText(QCoreApplication::translate("MainWindow", "x0.5", nullptr));
        actionx0_2->setText(QCoreApplication::translate("MainWindow", "x0.2", nullptr));
        actionx0_1->setText(QCoreApplication::translate("MainWindow", "x0.1", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        actionRemoveList->setText(QCoreApplication::translate("MainWindow", "\347\247\273\351\231\244\346\222\255\346\224\276\345\210\227\350\241\250", nullptr));
        pictureLabel->setText(QString());
        NameLabel->setText(QCoreApplication::translate("MainWindow", "\351\273\230\350\256\244\345\233\276\347\211\207", nullptr));
        TitleLabel->setText(QCoreApplication::translate("MainWindow", "\346\240\207\351\242\230", nullptr));
        SetLabel->setText(QCoreApplication::translate("MainWindow", "\344\270\223\350\276\221", nullptr));
        timeLabel->setText(QCoreApplication::translate("MainWindow", "\346\227\266\351\225\277", nullptr));
        ArtistLabel->setText(QCoreApplication::translate("MainWindow", "\346\255\214\346\211\213", nullptr));
        formatLabel->setText(QCoreApplication::translate("MainWindow", "\346\240\274\345\274\217", nullptr));
        playtimeLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        totaltimeLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        playModeButton->setText(QString());
        outloadButton->setText(QString());
        lastButton->setText(QString());
        playButton->setText(QString());
        nextButton->setText(QString());
        terminateButton->setText(QString());
        likeButton->setText(QString());
        volumeButton->setText(QString());
        fileMenu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        playMenu->setTitle(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276", nullptr));
        menuPlaySpeed->setTitle(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276\351\200\237\345\272\246", nullptr));
        menuSequence->setTitle(QCoreApplication::translate("MainWindow", "\346\222\255\346\224\276\346\254\241\345\272\217", nullptr));
        helpMenu->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
