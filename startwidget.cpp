#include "startwidget.h"
#include "mainwindow.h"

#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
/**
 * @brief StartWidget::StartWidget
 * 开始界面
 * @param parent：QT父对象指针
 */
StartWidget::StartWidget(QWidget *parent) : QWidget(parent),
    m_mainWindow(nullptr){
    setMinimumSize(1100,550);
    setMaximumSize(1100,550);
    setWindowIcon (QIcon(":/images/res/snake.jpeg"));
    setWindowTitle (tr("RetroSnaker"));
    QPalette palette;
    palette.setBrush (QPalette::Background, QBrush(QPixmap(":/images/res/startbgp.jpeg").scaled (this->size ())));
    setPalette(palette);
    m_onePlayer = new QPushButton(this);
    m_onePlayer->setIcon(QIcon(":/images/res/1P.png"));
    m_onePlayer->setIconSize(QSize(80,80));
    m_onePlayer->setGeometry(450,400,90,90);
    m_twoPlayer = new QPushButton(this);
    m_twoPlayer->setIcon(QIcon(":/images/res/2P.png"));
    m_twoPlayer->setIconSize(QSize(80,80));
    m_twoPlayer->setGeometry(550,400,90,90);
    connect(m_onePlayer,&QPushButton::clicked,this,&StartWidget::onePlayer);
    connect(m_twoPlayer,&QPushButton::clicked,this,&StartWidget::twoPlayer);

}
/**
 * @brief StartWidget::~StartWidget
 */
StartWidget::~StartWidget(){}
/**
 * @brief StartWidget::onePlayer
 * 槽函数：选择单玩家
 */
void StartWidget::onePlayer(){
    bool ok;
    QString name = QInputDialog::getText(this,tr("Input Name"),tr("NAME"),QLineEdit::Normal,tr("palyer"),&ok);
    if (ok && !name.isEmpty()){
        m_mainWindow = new MainWindow(true,this);
        connect(m_mainWindow,&MainWindow::showStartWidget,this,&StartWidget::reLoadWidget);
        m_mainWindow->setName(&name);
        this->hide();
        m_mainWindow->show();
        //this->close();
    } else{
        QMessageBox::information(this,tr(""),tr("Wrong name!"));
    }
}
/**
 * @brief StartWidget::twoPlayer
 * 槽函数：选择双玩家
 */
void StartWidget::twoPlayer(){
    m_mainWindow = new MainWindow(false,this);
    connect(m_mainWindow,&MainWindow::showStartWidget,this,&StartWidget::reLoadWidget);
    this->hide();
    m_mainWindow->show();
}
/**
 * @brief StartWidget::reLoadWidget
 * 槽函数：重新打开开始界面
 * @param pos：开始界面的位置
 */
void StartWidget::reLoadWidget(QPoint pos){
    this->show();
    this->move(pos);
}
