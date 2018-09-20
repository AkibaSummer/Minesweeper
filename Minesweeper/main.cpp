#include "Minesweeper.h"
#include <QApplication>
QString name_;
vector<Player> easPlLi;	//简单成绩列表
vector<Player> midPlLi;	//中等成绩列表
vector<Player> difPlLi;	//困难成绩列表
vector<Player> cosPlLi;	//自定成绩列表
int status_;
int difficulty_;
int score_;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Minesweeper w;
    w.showFullScreen();
    return a.exec();
}
