#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

#include "controller.h"
#include "food.h"
#include "wall.h"
#include "snake.h"
#include "constants.h"

/**
 * @brief Controller::Controller
 * @param scene ���������Ƶĳ���
 * @param is �Ƿ��ǵ���ģʽ
 * @param parent QT������ָ��
 */
Controller::Controller(QGraphicsScene &scene,bool is, QObject *parent) :
    QObject(parent),
    scene(scene),
    snake1(nullptr),
    snake2(nullptr),
    loser(nullptr),
    is1P(is){
    timer.start( 1000/33 );
    Food *a1 = new Food(new QGraphicsEllipseItem(QRectF(-BLOCK_SIZE/2,    -BLOCK_SIZE/2,
                                                        BLOCK_SIZE, BLOCK_SIZE)));
    a1->setColorPos(Qt::red,5,-45);
    scene.addItem(a1);

    if(is1P)
    {
        snake1 = new Snake(*this,0,0,Qt::green);
        scene.addItem(snake1);
    }
    else{
        snake1 = new Snake(*this,-50,0,Qt::green);
        scene.addItem(snake1);
        snake2 = new Snake(*this,50,0,Qt::yellow);
        scene.addItem(snake2);

    }
    scene.installEventFilter(this);
    addWall();
    resume();
}
/**
 * @brief Controller::~Controller
 */
Controller::~Controller(){
}

/**
 * @brief Controller::snakeAteFood
 * �߳Ե�ʳ������Ϊ
 * @param snake���߶���
 * @param food��ʳ�����
 */
void Controller::snakeAteFood(Snake *snake,Food *food){
    scene.removeItem(food);
    delete food;
    addNewFood();
    if(snake == snake1)
        emit snake1Scored(snake1->getScore());
    else emit snake2Scored(snake2->getScore());
}
/**
 * @brief Controller::snakeHitWall
 * ��ײǽ�����Ϊ
 * @param snake���߶���
 */
void Controller::snakeHitWall(Snake *snake){
    loser = snake;
    QTimer::singleShot(0, this, SLOT(gameOver()));
}
/**
 * @brief Controller::snakeAteItself
 * �߳Ե��Լ������Ϊ
 * @param snake���߶���
 */
void Controller::snakeAteItself(Snake *snake){
    loser = snake;
    QTimer::singleShot(0, this, SLOT(gameOver()));
}
/**
 * @brief Controller::snakeHitOther
 * ��ײ�������ߺ����Ϊ
 * @param snake���߶���
 */
void Controller::snakeHitOther(Snake *snake){
    loser = snake;
    QTimer::singleShot(0, this, SLOT(gameOver()));
}
/**
 * @brief Controller::head2head
 * ������ͷײͷ�����Ϊ
 */
void Controller::head2head(){
    int score1 = snake1->getScore();
    int score2 = snake2->getScore();
    if(score1>score2){
        loser = snake2;
    }else if(score1<score2){
        loser = snake1;
    }else loser = nullptr;
    QTimer::singleShot(0, this, SLOT(gameOver()));
}
/**
 * @brief Controller::handleKeyPressed
 * �������¼�
 * @param event�������¼�
 */
void Controller::handleKeyPressed(QKeyEvent *event){
    switch (event->key()) {
        case Qt::Key_Left:
            snake1->setMoveDirection(Snake::MoveLeft);
            break;
        case Qt::Key_Right:
            snake1->setMoveDirection(Snake::MoveRight);
            break;
        case Qt::Key_Up:
            snake1->setMoveDirection(Snake::MoveUp);
            break;
        case Qt::Key_Down:
            snake1->setMoveDirection(Snake::MoveDown);
            break;
        case Qt::Key_A:
            if(!is1P)
                snake2->setMoveDirection(Snake::MoveLeft);
            break;
        case Qt::Key_D:
            if(!is1P)
                snake2->setMoveDirection(Snake::MoveRight);
            break;
        case Qt::Key_W:
            if(!is1P)
                snake2->setMoveDirection(Snake::MoveUp);
            break;
        case Qt::Key_S:
            if(!is1P)
                snake2->setMoveDirection(Snake::MoveDown);
            break;
    }
}
/**
 * @brief Controller::addNewFood
 * �������µ�ʳ��
 */
void Controller::addNewFood(){
    int x, y;
    if(is1P){
        do {
            x = (int) (qrand() % 340)/10;
            y = (int) (qrand() % 180)/10;

            x = x*10-170;
            y = y*10-90;
        } while (snake1->shape().contains(snake1->mapFromScene(QPointF(x, y))));
    }else{
        do {
            x = (int) (qrand() % 340)/10;
            y = (int) (qrand() % 180)/10;

            x = x*10-170;
            y = y*10-90;
        } while (snake1->shape().contains(snake1->mapFromScene(QPointF(x, y)))||
                 snake2->shape().contains(snake2->mapFromScene(QPointF(x, y))));
    }
    Food *food = new Food(new QGraphicsEllipseItem(QRectF(-BLOCK_SIZE/2,    -BLOCK_SIZE/2,
                                                          BLOCK_SIZE, BLOCK_SIZE)));
    x=x>0?x-5:x+5;
    y=y>0?y+5:y-5;
    food->setColorPos(Qt::red,x,y);
    scene.addItem(food);
}

/**
 * @brief Controller::addWall
 * �ڳ��������ǽ��
 */
void Controller::addWall(){
    Wall *wallUp = new Wall(new QGraphicsRectItem(QRectF(-200,-105,400,14.5)));
    wallUp->setColor(QColor(150,75,0));
    Wall *wallLeft = new Wall(new QGraphicsRectItem(QRectF(-200,-90,29.5,180)));
    wallLeft->setColor(QColor(150,75,0));
    Wall *wallRight = new Wall(new QGraphicsRectItem(QRectF(170.5,-90,20,180)));
    wallRight->setColor(QColor(150,75,0));
    Wall *wallDown = new Wall(new QGraphicsRectItem(QRectF(-200,90.5,400,15)));
    wallDown->setColor(QColor(150,75,0));
    scene.addItem(wallUp);
    scene.addItem(wallDown);
    scene.addItem(wallLeft);
    scene.addItem(wallRight);
}

/**
 * @brief Controller::reSetController
 * ���ÿ�����
 */
void Controller::reSetController(){
    scene.clear();
     if(is1P)
     {
         snake1 = new Snake(*this,0,0,Qt::green);
         scene.addItem(snake1);
     }
     else{
         snake1 = new Snake(*this,-50,0,Qt::green);
         scene.addItem(snake1);
         snake2 = new Snake(*this,50,0,Qt::yellow);
         scene.addItem(snake2);
         loser = nullptr;

     }
     addNewFood();
     addWall();
}

/**
 * @brief Controller::gameOver
 * ��Ϸ����
 */
void Controller::gameOver(){

    if(is1P){
        int score = snake1->getScore();
        scene.clear();
        emit sendOver(score);
        }else{
        QString s;
        if(loser == snake2)
            s = "Player1 Win!";
        else if(loser == snake1)
            s = "Player2 Win!";
        else s = "It ends in a draw!";
        scene.clear();
        emit sendOver(s);
    }
}
/**
 * @brief Controller::pause
 * ��Ϸ��ͣ
 */
void Controller::pause(){
    disconnect(&timer, SIGNAL(timeout()),
               &scene, SLOT(advance()));
}
/**
 * @brief Controller::resume
 * ��Ϸ����
 */
void Controller::resume(){
    connect(&timer, SIGNAL(timeout()),
            &scene, SLOT(advance()));
}
/**
 * @brief Controller::eventFilter
 * �¼�������
 * @param object
 * @param event
 * @return
 */
bool Controller::eventFilter(QObject *object, QEvent *event){
    if (event->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    } else {
        return QObject::eventFilter(object, event);
    }
}
