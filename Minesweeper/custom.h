#ifndef CUSTOM_H
#define CUSTOM_H

#include <QWidget>
#include <QPaintEvent>
#include <QImage>
#include <QMouseEvent>
#include <QTimer>
#include <QString>
#include <QPainter>
#include <QMainWindow>
namespace Ui {
class Custom;
}

class Custom : public QWidget
{
    Q_OBJECT

public:
    int size_x=10,size_y=10,num_boom=10;
    QImage images;
    QPixmap maptemp=QPixmap(693,650);
    void init();
    void paintEvent(QPaintEvent*w);
    explicit Custom(QWidget *parent = nullptr);
    ~Custom();
private slots:
    void on_pushButton2_clicked();
    void on_pushButton1_clicked();
signals:
    void setCustomInfo(int,int,int,int);
private:
    Ui::Custom *ui;

};

#endif // CUSTOM_H
