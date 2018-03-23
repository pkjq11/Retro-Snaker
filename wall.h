#ifndef WALL_H
#define WALL_H
#include "graphicsitemdecorator.h"
class QColor;
/**
 * @brief The Wall class
 * ǽ����
 */
class Wall : public GraphicsItemDecorator
{
public:
    Wall(QGraphicsItem* item);
    virtual ~Wall();
    void setColor(QColor color);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
private:
    QColor m_color;//ǽ�����ɫ
};

#endif // WALL_H
