#include <QPainter>

#include "constants.h"
#include "food.h"

/**
 * @brief Food::Food
 * @param item：充当食物的圆形部件
 */
Food::Food(QGraphicsItem* item){
    setData(GD_Type, GO_Food);
    setComponent(item);
}
Food::~Food(){}

/**
 * @brief Food::setColorPos
 * @param color 颜色
 * @param x 横坐标
 * @param y 纵坐标
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
