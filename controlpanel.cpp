#include <QPainter>
#include <QLCDNumber>
#include <QLabel>

#include "controlpanel.h"
/**
 * @brief ControlPanel::ControlPanel
 * @param parent：QT父对象指针
 */
ControlPanel::ControlPanel(QWidget *parent) : QWidget(parent){
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    setMinimumSize(250,500);
    setMaximumSize(250,500);
    initLCD();
    initLabel();
}
/**
 * @brief ControlPanel::paintEvent
 * @see QWidget
 */
void ControlPanel::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QImage *pimage=new QImage(":images/res/description.png");
    painter.drawImage(rect(),*pimage);
}
/**
 * @brief ControlPanel::initLCD
 * 初始化LCD面板
 */
void ControlPanel::initLCD(){
    player1LCD = new QLCDNumber(this);
    player1LCD->setGeometry(120,150,120,60);
    player1LCD->setDigitCount(4);
    player1LCD->setStyleSheet("color: red;background: black;");
    player2LCD = new QLCDNumber(this);
    player2LCD->setGeometry(120,400,120,60);
    player2LCD->setDigitCount(4);
    player2LCD->setStyleSheet("color: red;background: black;");

}
/**
 * @brief ControlPanel::initLabel
 * 初始化标签面板
 */
void ControlPanel::initLabel(){
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::black);
    QFont ft;
    ft.setPointSize(24);
    player1Score = new QLabel(this);
    player1Score->setText(tr("Score"));
    player1Score->setPalette(pe);
    player1Score->setFont(ft);
    player1Score->setGeometry(120,100,120,60);
    player2Score = new QLabel(this);
    player2Score->setText(tr("Score"));
    player2Score->setPalette(pe);
    player2Score->setFont(ft);
    player2Score->setGeometry(120,350,120,60);
}
/**
 * @brief ControlPanel::setPlayer1LCD
 * 设置玩家1的LCD面板值
 * @param score：分数
 */
void ControlPanel::setPlayer1LCD(int score){
    player1LCD->display(score);
}
/**
 * @brief ControlPanel::setPlayer2LCD
 * 设置玩家2的LCD面板值
 * @param score：分数
 */
void ControlPanel::setPlayer2LCD(int score){
    player2LCD->display(score);
}
/**
 * @brief ControlPanel::~ControlPanel
 */
ControlPanel::~ControlPanel(){
}
