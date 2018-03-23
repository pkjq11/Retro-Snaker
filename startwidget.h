#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
class QPushButton;
class MainWindow;

/**
 * @brief The StartWidget class
 * 开始界面
 */
class StartWidget : public QWidget{
    Q_OBJECT
public:
    explicit StartWidget(QWidget *parent = nullptr);
    ~StartWidget();

private:
    //void closeEvent(QCloseEvent *);

    QPushButton *m_onePlayer;   //但玩家按钮
    QPushButton *m_twoPlayer;   //双玩家按钮
    MainWindow *m_mainWindow;   //游戏区

signals:

public slots:
    void onePlayer();
    void twoPlayer();
    void reLoadWidget(QPoint pos);
};

#endif // STARTWIDGET_H
