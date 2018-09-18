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
    int loc=1;
    Game game;
    int diff;
};

#endif // MAINWINDOW_H
