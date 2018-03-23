#include <QGraphicsView>
#include <QTimer>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QSplitter>
#include <QMessageBox>

#include "controller.h"
#include "constants.h"
#include "controlpanel.h"
#include "rankdialog.h"
#include "mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * ��ʼ�������ڽ���
 * @param is���Ƿ��ǵ����
 * @param parent��QT������ָ��
 */
MainWindow::MainWindow(bool is,QWidget *parent)
    : QMainWindow(parent),
      m_scene(new QGraphicsScene(this)),
      m_view(new QGraphicsView(m_scene, this)),
      m_controller(new Controller(*m_scene,is,this)),
      m_musicPlayer(new QMediaPlayer(this)),
      m_controlPanel(new ControlPanel(this)),
      m_splitter(new QSplitter(Qt::Horizontal,this)),
      m_rankDialog(new RankDialog(this)),
      isOnePlayer(is){
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowIcon(QIcon(":/images/res/snake.jpeg"));
    setCentralWidget(m_splitter);
    setMinimumSize(1100,550);
    setMaximumSize(1100,550);
    move(parent->pos());

    m_splitter->addWidget(m_view);
    m_splitter->addWidget(m_controlPanel);

    restartGameAction = new QAction(QIcon(":/images/res/restart.png"),tr("Restart"),this);
    endGameAction = new QAction(QIcon(":/images/res/end.png"),tr("End"),this);
    rankingAction = new QAction(QIcon(":/images/res/ranking.png"),tr("Rank"),this);
    musicAction = new QAction(QIcon(":/images/res/music.png"),tr("music"),this);
    restartGameAction->setStatusTip(tr("Restart a new game"));
    endGameAction->setStatusTip(tr("End the game"));
    rankingAction->setStatusTip(tr("Show the ranking"));
    musicAction->setStatusTip(tr("Turn on/off music"));
    m_view->setStatusTip(tr("Game Region"));
    m_controlPanel->setStatusTip(tr("Description and fraction"));

    statusBar();
    QMenu *game = menuBar()->addMenu(tr("game"));
    game->addAction(restartGameAction);
    game->addAction(endGameAction);
    QMenu *tools = menuBar()->addMenu(tr("tools"));
    tools->addAction(rankingAction);
    tools->addAction(musicAction);
    QToolBar *toolBar = addToolBar(tr("tools"));
    toolBar->addAction(restartGameAction);
    toolBar->addAction(endGameAction);
    toolBar->addAction(rankingAction);
    toolBar->addAction(musicAction);


    initMusic();
    initScene();
    initSceneBackground();


    QTimer::singleShot(0, this, SLOT(adjustViewSize()));
    connect(rankingAction,&QAction::triggered,this,&MainWindow::showRanking);
    connect(musicAction,&QAction::triggered,this,&MainWindow::onOffMusic);
    connect(restartGameAction,&QAction::triggered,m_controller,&Controller::reSetController);
    connect(endGameAction,&QAction::triggered,m_controller,&Controller::gameOver);
    connect(this,&MainWindow::updateRank,m_rankDialog,&RankDialog::update);
    connect(m_controller,SIGNAL(sendOver(QString)),this,SLOT(gameOver(QString)));
    connect(m_controller,SIGNAL(sendOver(int)),this,SLOT(gameOver(int)));
    connect(m_musicPlayer,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(reStartMusic(QMediaPlayer::State)));
    connect(m_controller,SIGNAL(snake1Scored(int)),this,SLOT(player1ScoreChange(int)));
    connect(m_controller,SIGNAL(snake2Scored(int)),this,SLOT(player2ScoreChange(int)));
}
/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow(){

}
/**
 * @brief MainWindow::adjustViewSize
 * �ۺ��������������ӽǳߴ�
 */
void MainWindow::adjustViewSize(){
    m_view->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}
/**
 * @brief MainWindow::onOffMusic
 * �ۺ��������ݲ�����״̬���ز�����
 */
void MainWindow::onOffMusic(){
    if(QMediaPlayer::PlayingState == m_musicPlayer->state()){
        m_musicPlayer->pause();
    }else{
        m_musicPlayer->play();
    }
}
/**
 * @brief MainWindow::reStartMusic
 * �ۺ����������ֲ�������Զ����²���
 * @param state����������״̬
 */
void MainWindow::reStartMusic(QMediaPlayer::State state){
    if(state == QMediaPlayer::StoppedState){
        m_musicPlayer->setPosition(0);
        m_musicPlayer->play();
    }

}
/**
 * @brief MainWindow::showRanking
 * �ۺ�������ʾ�������
 */
void MainWindow::showRanking(){
    m_rankDialog->exec();
}
/**
 * @brief MainWindow::gameOver
 * �ۺ���������ģʽ��Ϸ����
 * @param score������
 */
void MainWindow::gameOver(int score){
    QString s = QString("You get %1!").arg(score);
    emit updateRank(userName,score);
    overDialog(&s);
}
/**
 * @brief MainWindow::gameOver
 * �ۺ�����˫��ģʽ��Ϸ����
 * @param winner��ʤ��
 */
void MainWindow::gameOver(QString winner){
    overDialog(&winner);
}
/**
 * @brief MainWindow::player1ScoreChange
 * �ۺ��������1�����任
 * @param score������
 */
void MainWindow::player1ScoreChange(int score){
   m_controlPanel->setPlayer1LCD(score);
}
/**
 * @brief MainWindow::player2ScoreChange
 * �ۺ��������2�����仯
 * @param score������
 */
void MainWindow::player2ScoreChange(int score){
    m_controlPanel->setPlayer2LCD(score);
}
/**
 * @brief MainWindow::overDialog
 * ��ʾ�����Ի���
 * @param s����ʾ����
 */
void MainWindow::overDialog(QString *s){
    if(QMessageBox::Yes == QMessageBox::question(this,
                                                 tr("Game over"),
                                                 QString("%1\nAgain").arg(*s),
                                                 QMessageBox::Yes | QMessageBox::No,
                                                 QMessageBox::Yes)){
        m_controlPanel->setPlayer1LCD(0);
        m_controlPanel->setPlayer2LCD(0);
        m_controller->reSetController();
    }else{
        emit showStartWidget(this->pos());
        this->close();
    }
}
/**
 * @brief MainWindow::initMusic
 * ��ʼ�����ֲ�����
 */
void MainWindow::initMusic(){
    m_musicPlayer->setMedia(QUrl("qrc:/music/res/numb.mp3"));
    m_musicPlayer->setVolume(50);
    m_musicPlayer->play();
}
/**
 * @brief MainWindow::initScene
 * ��ʼ������
 */
void MainWindow::initScene(){
    m_scene->setSceneRect(-200, -100, 400, 200);
}
/**
 * @brief MainWindow::initSceneBackground
 * ��ʼ����������
 */
void MainWindow::initSceneBackground(){
    QPixmap bg(BLOCK_SIZE, BLOCK_SIZE);
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::gray));
    p.drawRect(0, 0, BLOCK_SIZE, BLOCK_SIZE);

    m_view->setBackgroundBrush(QBrush(bg));
    m_view->setStyleSheet("padding:0px;border:0px");
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
/**
 * @brief MainWindow::setName
 * �����������
 * @param name
 */
void MainWindow::setName(QString *name){
    userName = *name;
}
