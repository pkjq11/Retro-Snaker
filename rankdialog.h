#ifndef RANKDIALOG_H
#define RANKDIALOG_H

#include <QDialog>

class QTextEdit;
class QFile;
/**
 * @brief The item struct
 * ÿ���ɼ�����Ŀ
 */
struct item{
    QString id;         //����
    QString name;       //����
    QString score;      //����
};

/**
 * @brief The RankDialog class
 * ��Ϸ�������
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

    QTextEdit* m_rankpanel;     //չʾ�ɼ����ı���
    QVector<item> m_ranking;      //������гɼ�������
};

#endif // RANKDIALOG_H
