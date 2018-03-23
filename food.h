#ifndef FOOD_H
#define FOOD_H

#include "graphicsitemdecorator.h"
class QColor;
/**
 * @brief The Food class
 * 游戏中蛇的食物类
 */
class Food : public GraphicsItemDecorator{
public:
    Food(QGraphicsItem* item);
    virtual ~Food();
    void setColorPos(QColor color,qreal x, qreal y);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
private:
    QColor m_color;     //食物的颜色
};

#endif // FOOD_H
