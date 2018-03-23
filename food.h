#ifndef FOOD_H
#define FOOD_H

#include "graphicsitemdecorator.h"
class QColor;
/**
 * @brief The Food class
 * ��Ϸ���ߵ�ʳ����
 */
class Food : public GraphicsItemDecorator{
public:
    Food(QGraphicsItem* item);
    virtual ~Food();
    void setColorPos(QColor color,qreal x, qreal y);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
private:
    QColor m_color;     //ʳ�����ɫ
};

#endif // FOOD_H
