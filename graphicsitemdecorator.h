#ifndef GRAPHICSITEMDECORATOR_H
#define GRAPHICSITEMDECORATOR_H

#include <QGraphicsItem>
/**
 * @brief The GraphicsItemDecorator class
 * �����пؼ���װ������
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
    QGraphicsItem* m_item;      //��װ��ʵ��
};

#endif // GRAPHICSITEMDECORATOR_H
