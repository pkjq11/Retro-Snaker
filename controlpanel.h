#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
class QLCDNumber;
class QLabel;
/**
 * @brief The ControlPanel class
 * 控制面板，用于展示游戏的控制方式以及玩家的分数
 */
class ControlPanel : public QWidget{
    Q_OBJECT
public:
    explicit ControlPanel(QWidget *parent = nullptr);
    void setPlayer1LCD(int score);
    void setPlayer2LCD(int score);
    ~ControlPanel();

protected:
    void paintEvent(QPaintEvent *event);


private:
    void initLCD();
    void initLabel();
    QLCDNumber *player1LCD; //指向玩家1的LCD面板
    QLCDNumber *player2LCD; //指向玩家2的LCD面板
    QLabel *player1Score;   //指向玩家1的LCD面板的标签
    QLabel *player2Score;   //指向玩家2的LCD面板的标签
};

#endif // CONTROLPANEL_H
