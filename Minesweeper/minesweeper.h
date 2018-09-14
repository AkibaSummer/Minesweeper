#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <bits/stdc++.h>
#include <QMainWindow>
#include <QPaintEvent>
#include <QImage>
#include <QMouseEvent>
#include <QTimer>
#include <QString>
#include <QPainter>
using namespace std;

namespace Ui {
class Minesweeper;
}

class Minesweeper : public QMainWindow
{
    Q_OBJECT

public:
    int height=8;
    int weight=8;
    int bum=10;
    QImage images;
    QPixmap maptemp=QPixmap(1920,1080);

    void init();
    void paintEvent(QPaintEvent*w);
    void mousePressEvent(QMouseEvent*m);

    explicit Minesweeper(QWidget *parent = 0);
    ~Minesweeper();

private slots:

private:
    Ui::Minesweeper *ui;
};

#endif // MINESWEEPER_H
