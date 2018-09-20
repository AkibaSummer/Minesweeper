#ifndef THEENDWIDGET_H
#define THEENDWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QImage>
#include <QMouseEvent>
#include <QTimer>
#include <QString>
#include <QPainter>
#include <QMainWindow>
#include "rank.h"
#include "game.h"

namespace Ui {
class TheEndWidget;
}

class TheEndWidget : public QWidget
{
    Q_OBJECT

public:
    QImage images;
    QPixmap maptemp=QPixmap(685,633);
    void init();
    void inlabel(int,QString,int);
    void paintEvent(QPaintEvent*w);

    explicit TheEndWidget(QWidget *parent = nullptr);
    ~TheEndWidget();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::TheEndWidget *ui;
    Game newGame;
    Rank newRank;//排行榜
    Ranking rank;//结构体
    MapStatus maps=MapStatus(0,0);//含参构造函数，需要传参数
};

#endif // THEENDWIDGET_H
