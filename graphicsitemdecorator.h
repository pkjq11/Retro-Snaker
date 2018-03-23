#ifndef GRAPHICSITEMDECORATOR_H
#define GRAPHICSITEMDECORATOR_H

#include <QGraphicsItem>
/**
 * @brief The GraphicsItemDecorator class
 * 场景中控件的装饰器类
 */
class GraphicsItemDecorator: public QGraphicsItem
{
public:
    GraphicsItemDecorator();
    virtual ~GraphicsItemDecorator();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);
    virtual QPainterPath shape() const;

    virtual void setComponent(QGraphicsItem* item);

protected:
    QGraphicsItem* m_item;      //包装的实体
};

#endif // GRAPHICSITEMDECORATOR_H
