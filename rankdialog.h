#ifndef RANKDIALOG_H
#define RANKDIALOG_H

#include <QDialog>

class QTextEdit;
class QFile;
/**
 * @brief The item struct
 * 每条成绩的条目
 */
struct item{
    QString id;         //排名
    QString name;       //姓名
    QString score;      //分数
};

/**
 * @brief The RankDialog class
 * 游戏排名面板
 */
class RankDialog:public QDialog{
    Q_OBJECT
public:
    explicit RankDialog(QWidget *parent = 0);
    ~RankDialog();
    int update(QString name,int score);

private:
    void writeTextWidget();
    void writeText();

    QTextEdit* m_rankpanel;     //展示成绩的文本框
    QVector<item> m_ranking;      //存放所有成绩的容器
};

#endif // RANKDIALOG_H
