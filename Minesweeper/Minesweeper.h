#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QPainter"
#include "QMouseEvent"
#include "rule.h"
#include "QTimer"
#include "QString"
#include "custom.h"
#include "game.h"

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
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPixmap maptemp=QPixmap(1920,1080);
    QPixmap pix;

    void init();
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);
    void ruleOfGame();
    void customOfGame();
    void changeBackGround(QString);
    void loadGame(int,int,int,int);//diff x y num
    void drawGame();
private slots:
    void closeThis();
    void setCustomGame(int,int,int,int);
private:
    Ui::MainWindow *ui;
    Rule ru;
    Custom cu;
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
        ":/images/Sea/U1.jpg"
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
};

#endif // MAINWINDOW_H
