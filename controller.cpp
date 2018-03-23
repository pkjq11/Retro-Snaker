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
 * @param scene 控制器控制的场景
 * @param is 是否是单人模式
 * @param parent QT父对象指针
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
 * 蛇吃到食物后的行为
 * @param snake：蛇对象
 * @param food：食物对象
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
 * 蛇撞墙后的行为
 * @param snake：蛇对象
 */
void Controller::snakeHitWall(Snake *snake){
    loser = snake;
    QTimer::singleShot(0, this, SLOT(gameOver()));
}
/**
 * @brief Controller::snakeAteItself
 * 蛇吃到自己后的行为
 * @param snake：蛇对象
 */
void Controller::snakeAteItself(Snake *snake){
    loser = snake;
    QTimer::singleShot(0, this, SLOT(gameOver()));
}
/**
 * @brief Controller::snakeHitOther
 * 蛇撞到其他蛇后的行为
 * @param snake：蛇对象
 */
void Controller::snakeHitOther(Snake *snake){
    loser = snake;
    QTimer::singleShot(0, this, SLOT(gameOver()));
}
/**
 * @brief Controller::head2head
 * 两条蛇头撞头后的行为
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
 * 处理按键事件
 * @param event：按键事件
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
 * 随机添加新的食物
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
 * 在场景中添加墙体
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
 * 重置控制器
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
 * 游戏结束
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
 * 游戏暂停
 */
void Controller::pause(){
    disconnect(&timer, SIGNAL(timeout()),
               &scene, SLOT(advance()));
}
/**
 * @brief Controller::resume
 * 游戏继续
 */
void Controller::resume(){
    connect(&timer, SIGNAL(timeout()),
            &scene, SLOT(advance()));
}
/**
 * @brief Controller::eventFilter
 * 事件过滤器
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
