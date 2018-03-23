#include "graphicsitemdecorator.h"

GraphicsItemDecorator::GraphicsItemDecorator(){
}

GraphicsItemDecorator::~GraphicsItemDecorator(){
    delete m_item;
}
/**
 * @brief GraphicsItemDecorator::setComponent
 * ÉèÖÃÊµÌå
 * @param item
 */
void GraphicsItemDecorator::setComponent(QGraphicsItem* item){
    m_item = item;
}
/**
 * @brief GraphicsItemDecorator::boundingRect
 * @see QGraphicsItem
 * @return
 */
QRectF GraphicsItemDecorator::boundingRect() const{
    return m_item->boundingRect();
}
/**
 * @brief GraphicsItemDecorator::paint
 * @see QGraphicsItem
 * @param painter
 * @param item
 * @param widget
 */
void GraphicsItemDecorator::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget){
    m_item->paint(painter,item,widget);
}
/**
 * @brief GraphicsItemDecorator::shape
 * @see QGraphicsItem
 * @return
 */
QPainterPath GraphicsItemDecorator::shape() const{
    return m_item->shape();
}
