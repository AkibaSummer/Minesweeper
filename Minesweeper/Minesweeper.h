#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include "QPainter"
#include "QMouseEvent"
#include "rule.h"
#include "QTimer"
#include "QString"
#include "custom.h"
#include "game.h"
#include "rank.h"
#include "setname.h"
#include "ui_Minesweeper.h"
#include "theendwidget.h"

const int centerX=1040;
const int centerY=550;

struct Res{
    QString img_01;
    QString img_04;
    QString img_05;
    QString img_14;
    QString img_15;
    QString img_gameBack;
    QString img_menu;
    QString img_U;
    QString level;
};

struct Img{
    QPixmap img_01;
    QPixmap img_04;
    QPixmap img_05;
    QPixmap img_14;
    QPixmap img_15;
    QPixmap img_gameBack;
    QPixmap img_menu;
    QPixmap img_U;
    QPixmap img_0201;
    QPixmap img_0202;
    QPixmap img_0203;
    QPixmap img_0204;
    QPixmap img_0205;
    QPixmap img_0206;
    QPixmap img_0207;
    QPixmap img_0208;
    QPixmap img_03;
    QPixmap img_11;
};

namespace Ui {
class Minesweeper;
}

class Minesweeper : public QMainWindow
{
    Q_OBJECT

public:
    explicit Minesweeper(QWidget *parent = nullptr);
    ~Minesweeper();

    QPixmap maptemp=QPixmap(1920,1080);
    QPixmap pix;
    QPixmap pix1;
    QPixmap pix2;
    //实现计时器所需要的两行
    QTimer *pTimer = new QTimer(this);
    QTime baseTime;
    int t;//ms制的时间值
    int clickTimes = 0;//地图被调用drawGame刷新的次数


    void init();
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    QString sp(int);
    QString getInfo(int,unsigned int);//从数组中读取玩家数据显示到排行榜
    void mouseDoubleClickEvent(QMouseEvent*);
    void ruleOfGame();
    void customOfGame();
    void changeBackGround(QString);
    void loadGame(int,int,int,int);//diff x y num
    void drawGame();
    void showTime();//计时器的触发函数
private slots:
    void closeThis();
    void setCustomGame(int,int,int,int);
    void updateTimeAndDisplay();//计时器内部槽函数
    void restart();
    void restartNew();
    void backToMenu();

private:
    Ui::Minesweeper *ui;
    Rule ru;
    Custom cu;
    Rank ra;
    double opacity=0.0;
    QString picDir_;
    Res res={
        ":/images/Sea/01.png",
        ":/images/Sea/04.png",
        ":/images/Sea/05.jpg",
        ":/images/Sea/14.jpg",
        ":/images/Sea/15.jpg",
        ":/images/Sea/gameBack.png",
        ":/images/Sea/menu1.jpg",
        ":/images/Sea/U1.jpg",
        "Easy"
    };
    Img img={
        QPixmap(res.img_01),
        QPixmap(res.img_04),
        QPixmap(res.img_05),
        QPixmap(res.img_14),
        QPixmap(res.img_15),
        QPixmap(res.img_gameBack),
        QPixmap(res.img_menu),
        QPixmap(res.img_U),
        QPixmap(":/images/0201.png"),
        QPixmap(":/images/0202.png"),
        QPixmap(":/images/0203.png"),
        QPixmap(":/images/0204.png"),
        QPixmap(":/images/0205.png"),
        QPixmap(":/images/0206.png"),
        QPixmap(":/images/0207.png"),
        QPixmap(":/images/0208.png"),
        QPixmap(":/images/03.png"),
        QPixmap(":/images/11.png"),
    };
    int loc=1;
    Game game;
    int diff;
    SetName setName;
    TheEndWidget endw;
};

#endif // MAINWINDOW_H
