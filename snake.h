#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QRectF>

class Controller;
/**
 * @brief The Snake class
 * ����
 */
class Snake : public QGraphicsItem{
public:
    /**
     * @brief The Direction enum
     * ö�٣��ߵ��˶�����
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

    QPointF        head;            //��ͷλ��
    int            growing;         //������������
    int            speed;           //�������ƶ����ٶȣ�ֵԽ���ƶ�Խ��
    int            score;           //�÷�
    QList<QPointF> tail;            //���β��������
    int            tickCounter;     //ʱ�Ӽ���
    Direction      moveDirection;   //�ƶ��ķ���
    Controller &controller;         //���Ƹ��ߵĿ�����
    QBrush m_brush;                 //���������ɫ
};

#endif // SNAKE_H
