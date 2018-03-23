#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
class QLCDNumber;
class QLabel;
/**
 * @brief The ControlPanel class
 * ������壬����չʾ��Ϸ�Ŀ��Ʒ�ʽ�Լ���ҵķ���
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
    QLCDNumber *player1LCD; //ָ�����1��LCD���
    QLCDNumber *player2LCD; //ָ�����2��LCD���
    QLabel *player1Score;   //ָ�����1��LCD���ı�ǩ
    QLabel *player2Score;   //ָ�����2��LCD���ı�ǩ
};

#endif // CONTROLPANEL_H
