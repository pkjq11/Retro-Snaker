#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

class QGraphicsScene;
class QGraphicsView;
class Controller;
class ControlPanel;
class RankDialog;
class QSplitter;
/**
 * @brief The MainWindow class
 * 游戏主界面窗口
 */
class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(bool is,QWidget *parent = 0);
    ~MainWindow();

private slots:
    void adjustViewSize();
    void onOffMusic();
    void reStartMusic(QMediaPlayer::State state);
    void showRanking();
    void gameOver(int score);
    void gameOver(QString winner);
    void player1ScoreChange(int score);
    void player2ScoreChange(int score);
signals:
    void showStartWidget(QPoint);
    void updateRank(QString,int);

public:
    void setName(QString *name);
private:
    void initScene();
    void initSceneBackground();
    void initMusic();
    void overDialog(QString *s);


    QGraphicsScene *m_scene;        //游戏的场景
    QGraphicsView *m_view;          //游戏场景的视角
    Controller *m_controller;       //游戏的控制器
    QMediaPlayer *m_musicPlayer;    //背景音乐播放器
    ControlPanel *m_controlPanel;   //游戏的控制面板
    QSplitter *m_splitter;          //分割器，用于布局
    RankDialog *m_rankDialog;       //排名面板

    QAction *restartGameAction;     //动作：重新开始游戏
    QAction *endGameAction;         //动作：结束游戏
    QAction *rankingAction;         //动作：显示排名
    QAction *musicAction;           //动作：开关音乐

    bool isOnePlayer;               //是否是单玩家
    QString userName;               //单玩家时玩家的姓名
};

#endif // MAINWINDOW_H
