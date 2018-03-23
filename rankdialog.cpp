#include<QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QVector>

#include "rankdialog.h"

/**
 * @brief RankDialog::RankDialog
 * 排名面板
 * @param parent：QT父对象指针
 */
RankDialog::RankDialog(QWidget *parent):QDialog(parent),
    m_rankpanel(new QTextEdit(this))
{

    setWindowTitle(tr("Ranking List"));
    setFixedSize(200,200);
    m_rankpanel->setReadOnly(true);
    QFile ranTxt("ranking.txt");
    if(ranTxt.open(QFile::ReadOnly)){
        QTextStream data(&ranTxt);
        QString line;
        while(!data.atEnd()){
            line = data.readLine();
            QStringList lineList = line.split(" ",QString::SkipEmptyParts);
            item temp;
            temp.id = lineList[0];
            temp.name = lineList[1];
            temp.score = lineList[2];
            m_ranking.push_back(temp);
        }
    }
    ranTxt.close();
    writeTextWidget();
}
/**
 * @brief RankDialog::~RankDialog
 */
RankDialog::~RankDialog(){
}

/**
 * @brief RankDialog::writeText
 * 将成绩写入文本文件
 */
void RankDialog::writeText(){
    QFile ranTxt("ranking.txt");
    if(ranTxt.open(QFile::WriteOnly | QIODevice::Truncate)){
        QTextStream data(&ranTxt);
        for(auto iter = m_ranking.begin();iter != m_ranking.end();iter++){
            QString temp = QString("%1 %2 %3\n").arg(iter->id).arg(iter->name).arg(iter->score);
            data<<temp;
        }
    }
    ranTxt.close();
}
/**
 * @brief RankDialog::writeTextWidget
 * 将文本文件中的成绩写入排名面板
 */
void RankDialog::writeTextWidget(){
    m_rankpanel->clear();
    for(auto iter = m_ranking.begin();iter != m_ranking.end();iter++){
        QString temp = QString("%1\t%2\t%3").arg(iter->id).arg(iter->name).arg(iter->score);
        m_rankpanel->append(temp);
    }
}
/**
 * @brief RankDialog::update
 * 插入新的战绩
 * @param name ：玩家姓名
 * @param score：玩家成绩
 * @return ：玩家排名，只记录前10名，返回0表示不在前十名以内
 */
int RankDialog::update(QString name, int score){
    auto iter = m_ranking.rbegin();
    if(score <= (iter->score).toInt())
        return 0;
    int i = 10;
    iter++;
    for(;iter != m_ranking.rend();iter++){

        if((iter->score).toInt()<score){
            *(iter-1) = *iter;
            (iter-1)->id = QString("%1").arg((iter->id).toInt()+1);
            i--;
        }else {
            (iter-1)->score = QString("%1").arg(score);
            (iter-1)->name = name;
            (iter-1)->id = QString("%1").arg(i);
            break;
        }
    }
    writeTextWidget();
    writeText();
    return i;
}

