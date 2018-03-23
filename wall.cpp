#include <QPainter>

#include "constants.h"
#include "wall.h"

Wall::Wall(QGraphicsItem* item){
    setData(GD_Type, GO_Wall);
    setComponent(item);
}
Wall::~Wall(){}
/**
 * @brief Wall::setColor
 * ÉèÖÃÑÕÉ«
 * @param color
 */
void Wall::setColor(QColor color){

    m_color = color;
}

/**
 * @brief Food::paint
 * @see QGraphicsItem
 */
void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(), m_color);
    painter->restore();
}
