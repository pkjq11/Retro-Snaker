#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
class QPushButton;
class MainWindow;

/**
 * @brief The StartWidget class
 * ��ʼ����
 */
class StartWidget : public QWidget{
    Q_OBJECT
public:
    explicit StartWidget(QWidget *parent = nullptr);
    ~StartWidget();

private:
    //void closeEvent(QCloseEvent *);

    QPushButton *m_onePlayer;   //����Ұ�ť
    QPushButton *m_twoPlayer;   //˫��Ұ�ť
    MainWindow *m_mainWindow;   //��Ϸ��

signals:

public slots:
    void onePlayer();
    void twoPlayer();
    void reLoadWidget(QPoint pos);
};

#endif // STARTWIDGET_H
