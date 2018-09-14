#include "minesweeper.h"
#include "ui_minesweeper.h"
#include<QPainter>
#include<algorithm>
#include<ctime>
#include<QTimer>
#include<QString>

Minesweeper::Minesweeper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Minesweeper)
{
    ui->setupUi(this);
    //QPalette pal;
    //    pal.setColor(QPalette::WindowText, QColor(0,255,0));
    //    ui->lcdNumber->setPalette(pal);

    init();

}

void Minesweeper::init(){
    images.load(":/images/Anime/U3.jpg");
    QPainter pen(&maptemp);
    images=images.scaled(1920,1080,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pen.drawImage(0,0,images);
    srand(time(0));
    int centerX=1040,centerY=540;
    int width=18;
    int size = 980/width;

    images.load(":/images/Anime/16.png");
    images=images.scaled(size*width+20,size*width+20,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pen.drawImage(centerX-size*width/2-10,centerY-size*width/2-10,images);

    images.load(":/images/Anime/14.jpg");
    images=images.scaled(size-2,size-2,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    for (int i=-width/2;i<width/2;i++){
        for (int j=-width/2;j<width/2;j++){
            if (!(rand()%10))continue;
            pen.drawImage(centerX+1+size*i,centerY+1+size*j,images);
        }
    }

}

void Minesweeper::paintEvent(QPaintEvent*w){
    Q_UNUSED(w);
    QPainter pen(this);
    pen.drawPixmap(0,0,maptemp);
    /*images=images.scaled(1920,1080,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pen.drawImage(0,0,images);
    srand(time(0));
    int centerX=1040,centerY=540;
    int width=18;
    int size = 980/width;

    images.load(":/images/Anime/16.png");
    images=images.scaled(size*width+20,size*width+20,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pen.drawImage(centerX-size*width/2-10,centerY-size*width/2-10,images);

    images.load(":/images/Anime/14.jpg");
    images=images.scaled(size-2,size-2,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    for (int i=-width/2;i<width/2;i++){
        for (int j=-width/2;j<width/2;j++){
            if (!(rand()%10))continue;
            pen.drawImage(centerX+1+size*i,centerY+1+size*j,images);
        }
    }

    //QPolygonF polygon_dongbei(dongbei);
    //if(polygon_xibei.containsPoint(mouse,Qt::OddEvenFill))
    */
}

void Minesweeper::mousePressEvent(QMouseEvent*m){
    int x=m->x();
    int y=m->y();
    if (m->button()==Qt::LeftButton){
        QPainter pen(&maptemp);
        images.load(":/images/Anime/16.png");
        images=images.scaled(50,50);
        pen.drawImage(x-25,y-25,images);
        update();
    }
}
Minesweeper::~Minesweeper()
{
    delete ui;
}
