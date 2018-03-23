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
 * 游戏控制器类
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

    QTimer timer;           //定时器
    QGraphicsScene &scene;  //控制器控制的场景
    Snake *snake1;          //控制器控制的蛇1
    Snake *snake2;          //控制器控制的蛇2
    Snake *loser;           //指向失败的蛇
    bool is1P;              //是否是单玩家
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
