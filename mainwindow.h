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
 * ��Ϸ�����洰��
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


    QGraphicsScene *m_scene;        //��Ϸ�ĳ���
    QGraphicsView *m_view;          //��Ϸ�������ӽ�
    Controller *m_controller;       //��Ϸ�Ŀ�����
    QMediaPlayer *m_musicPlayer;    //�������ֲ�����
    ControlPanel *m_controlPanel;   //��Ϸ�Ŀ������
    QSplitter *m_splitter;          //�ָ��������ڲ���
    RankDialog *m_rankDialog;       //�������

    QAction *restartGameAction;     //���������¿�ʼ��Ϸ
    QAction *endGameAction;         //������������Ϸ
    QAction *rankingAction;         //��������ʾ����
    QAction *musicAction;           //��������������

    bool isOnePlayer;               //�Ƿ��ǵ����
    QString userName;               //�����ʱ��ҵ�����
};

#endif // MAINWINDOW_H
