#include <QPainter>

#include "constants.h"
#include "controller.h"
#include "snake.h"

/**
 * @brief Snake::Snake
 * @param controller��������
 * @param x ����ͷλ�ú�����
 * @param y ����ͷλ��������
 * @param brush���������ɫ
 */
Snake::Snake(Controller &controller,qreal x, qreal y,QBrush brush) :
    head(x, y),
    growing(1),
    speed(4),
    score(0),
    moveDirection(NoMove),
    controller(controller),
    m_brush(brush){
    setData(GD_Type, GO_Snake);
}

Snake::~Snake(){

}
/**
 * @brief Snake::boundingRect
 * @see QGraphicsItem
 */
QRectF Snake::boundingRect() const{
    qreal minX = head.x();
    qreal minY = head.y();
    qreal maxX = head.x();
    qreal maxY = head.y();

    foreach (QPointF p, tail) {
        maxX = p.x() > maxX ? p.x() : maxX;
        maxY = p.y() > maxY ? p.y() : maxY;
        minX = p.x() < minX ? p.x() : minX;
        minY = p.y() < minY ? p.y() : minY;
    }

    QPointF tl = mapFromScene(QPointF(minX, minY));
    QPointF br = mapFromScene(QPointF(maxX, maxY));
    QRectF bound = QRectF(tl.x(),  // x
                          tl.y(),  // y
                          br.x() - tl.x() + BLOCK_SIZE,      // width
                          br.y() - tl.y() + BLOCK_SIZE       //height
                          );
    return bound;
}
/**
 * @brief Snake::shape
 * @see QGraphicsItem
 */
QPainterPath Snake::shape() const{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    path.addRect(QRectF(head.x(), head.y(), BLOCK_SIZE, BLOCK_SIZE));

    foreach (QPointF p, tail) {
        QPointF itemp = mapFromScene(p);
        path.addRect(QRectF(itemp.x(), itemp.y(), BLOCK_SIZE, BLOCK_SIZE));
    }

    return path;
}
/**
 * @brief Snake::paint
 * @see QGraphicsItem
 */
void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->save();
    painter->fillPath(shape(), m_brush);
    painter->restore();
}

/**
 * @brief Snake::setMoveDirection
 * �����ߵ��˶�����
 * @param direction������
 */
void Snake::setMoveDirection(Direction direction){
    if(moveDirection*direction!=2&&moveDirection*direction!=12)
        moveDirection = direction;
}
/**
 * @brief Snake::isContains
 * �ж�ĳ�����Ƿ���������Χ
 * @param block�� ��λ��
 * @return ��/��
 */
bool Snake::isContains(QPointF block){
    return tail.contains(block);
}
/**
 * @brief Snake::advance
 * @see QGraphicsItem
 */
void Snake::advance(int step){
    if (!step) {
        return;
    }
    if (tickCounter++ % speed != 0) {
        return;
    }
    if (moveDirection == NoMove) {
        return;
    }

    if (growing > 0) {
		QPointF tailPoint = head;
        tail << tailPoint;
        growing -= 1;
    } else {
        tail.takeFirst();
        tail << head;

    }

    switch (moveDirection) {
        case NoMove:
            break;
        case MoveLeft:
            moveLeft();
            break;
        case MoveRight:
            moveRight();
            break;
        case MoveUp:
            moveUp();
            break;
        case MoveDown:
            moveDown();
            break;
    }

    setPos(head);
    handleCollisions();
}
/**
 * @brief Snake::moveLeft
 * �����ƶ��Ķ���
 */
void Snake::moveLeft(){
    head.rx() -= BLOCK_SIZE;
}
/**
 * @brief Snake::moveRight
 * �����ƶ��Ķ���
 */
void Snake::moveRight(){
    head.rx() += BLOCK_SIZE;
}
/**
 * @brief Snake::moveUp
 * �����ƶ��Ķ���
 */
void Snake::moveUp(){
    head.ry() -= BLOCK_SIZE;
}
/**
 * @brief Snake::moveDown
 * �����ƶ��Ķ���
 */
void Snake::moveDown(){
    head.ry() += BLOCK_SIZE;
}
/**
 * @brief Snake::handleCollisions
 * �����ߵ���ײ�¼�
 */
void Snake::handleCollisions(){
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *collidingItem, collisions) {
        if (collidingItem->data(GD_Type) == GO_Food) {
            growing += 1;
            score += 10;
            controller.snakeAteFood(this,(Food *)collidingItem);
            continue;
        }
        if (collidingItem->data(GD_Type) == GO_Wall){
            controller.snakeHitWall(this);
            continue;
        }
        if (collidingItem->data(GD_Type) == GO_Snake){
            Snake* temp = dynamic_cast<Snake*>(collidingItem);
            if(temp->isContains(head))
                controller.snakeHitOther(this);
            else if (temp->getHead()==head)
                controller.head2head();
            continue;
        }

    }
    if (tail.contains(head)) {
        controller.snakeAteItself(this);
    }

}
