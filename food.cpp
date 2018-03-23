#include <QPainter>

#include "constants.h"
#include "food.h"

/**
 * @brief Food::Food
 * @param item���䵱ʳ���Բ�β���
 */
Food::Food(QGraphicsItem* item){
    setData(GD_Type, GO_Food);
    setComponent(item);
}
Food::~Food(){}

/**
 * @brief Food::setColorPos
 * @param color ��ɫ
 * @param x ������
 * @param y ������
 */
void Food::setColorPos(QColor color,qreal x, qreal y){
    setPos(x,y);
    m_color = color;
}

/**
 * @brief Food::paint
 * @see QGraphicsItem
 */
void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(), m_color);
    painter->restore();
}
