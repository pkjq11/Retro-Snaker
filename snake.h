#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QRectF>

class Controller;
/**
 * @brief The Snake class
 * 蛇类
 */
class Snake : public QGraphicsItem{
public:
    /**
     * @brief The Direction enum
     * 枚举：蛇的运动方向
     */
    enum Direction {
        NoMove,
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown
    };

    Snake(Controller & controller,qreal x, qreal y,QBrush brush);
    ~Snake();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void setMoveDirection(Direction direction);
    bool isContains(QPointF block);
    inline QPointF getHead(){return head;}
    inline int getScore(){return score;}

protected:
    void advance(int step);

private:
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void handleCollisions();

    QPointF        head;            //蛇头位置
    int            growing;         //蛇增长的数量
    int            speed;           //控制蛇移动的速度，值越大移动越慢
    int            score;           //得分
    QList<QPointF> tail;            //存放尾部的容器
    int            tickCounter;     //时钟计数
    Direction      moveDirection;   //移动的方向
    Controller &controller;         //控制该蛇的控制器
    QBrush m_brush;                 //蛇身体的颜色
};

#endif // SNAKE_H
