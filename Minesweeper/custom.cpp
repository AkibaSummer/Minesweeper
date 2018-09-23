#include "custom.h"
#include "ui_custom.h"
#include <QPainter>
#include <QTimer>
#include <QString>
#include <QValidator>



Custom::Custom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Custom)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//隐藏边栏
    this->setWindowModality(Qt::ApplicationModal);//阻塞其他窗口

    init();
    update();
}

void Custom::init(){
    images.load(":/Custom/custom.jpg");
    QPainter pen(&maptemp);
    pen.drawImage(0,0,images);//画入背景图片

    QIcon queding(":/Custom/button1.jpg");
    this->ui->pushButton1->setIcon(queding);
    this->ui->pushButton1->setIconSize(QSize(190,65));//插入确定按钮图片
    this->ui->pushButton1->setFlat(true);//使按钮透明

    QIcon qvxiao(":/Custom/button2.jpg");
    this->ui->pushButton2->setIcon(qvxiao);
    this->ui->pushButton2->setIconSize(QSize(190,65));//插入取消按钮图片
    this->ui->pushButton2->setFlat(true);//使按钮透明


    QIntValidator *validator1 = new QIntValidator(8, 30, this);//设置文本框文本格式，限制大小
    this->ui->lineEdit1->setValidator(validator1);

    QIntValidator *validator2 = new QIntValidator(8, 30, this);
    this->ui->lineEdit2->setValidator(validator2);

    QIntValidator *validator3 = new QIntValidator(10, 841, this);
    this->ui->lineEdit3->setValidator(validator3);
}


void Custom::paintEvent(QPaintEvent*w){
    Q_UNUSED(w);
    QPainter pen(this);
    pen.drawPixmap(0,0,maptemp);
}

void Custom::on_pushButton2_clicked()//点击取消时调用
{
    this->close();
}//关闭自定义窗口

void Custom::on_pushButton1_clicked()//点击确定时调用
{
    size_x=this->ui->lineEdit1->text().toInt();
    size_y=this->ui->lineEdit2->text().toInt();
    num_boom=this->ui->lineEdit3->text().toInt();
    emit setCustomInfo(0,size_x,size_y,num_boom);
    this->close();//得到行数列数雷数，储存在三个QString对象中（后期调用数据），点击确定关闭自定义窗口
}
Custom::~Custom()
{
    delete ui;
}
