#ifndef Controller_H
#define Controller_H

#include <QObject>
#include <QTimer>

class QGraphicsScene;
class QKeyEvent;
class Food;
class Snake;
/**
 * @brief The Controller class
 * ��Ϸ��������
 */
class Controller : public QObject{
    Q_OBJECT
public:

    Controller(QGraphicsScene &scene,bool is, QObject *parent = 0);
     ~Controller();

    void snakeAteFood(Snake *snake,Food *food);
    void snakeHitWall(Snake *snake);
    void snakeAteItself(Snake *snake);
    void snakeHitOther(Snake *snake);
    void head2head();
    void reSetController();

private:
    bool eventFilter(QObject *object, QEvent *event);
    void handleKeyPressed(QKeyEvent *event);
    void addWall();
    void addNewFood();

    QTimer timer;           //��ʱ��
    QGraphicsScene &scene;  //���������Ƶĳ���
    Snake *snake1;          //���������Ƶ���1
    Snake *snake2;          //���������Ƶ���2
    Snake *loser;           //ָ��ʧ�ܵ���
    bool is1P;              //�Ƿ��ǵ����
public slots:
    void pause();
    void resume();
    void gameOver();
signals:
    void sendOver(QString winner);
    void sendOver(int score);
    void snake1Scored(int score);
    void snake2Scored(int score);
};

#endif // Controller_H
