#include "rule.h"
#include "ui_rule.h"
//#include "QtGui"

Rule::Rule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rule)
{
    ui->setupUi(this);
    //this->setWindowOpacity(0.2);//透明化窗口

    this->setWindowFlags(Qt::FramelessWindowHint);//隐藏边栏
    this->setWindowModality(Qt::ApplicationModal);//阻塞其他窗口

    QIcon icon;
    icon.addFile(tr(":/images/11.png"));
    this->ui->quit->setIcon(icon);

    connect(this->ui->quit,SIGNAL(clicked(bool)),this,SLOT(closeThis()));

    showRule();
}

void Rule::showRule()
{
    QPainter pen(&maptemp);
    //QImage images;
    //images.load(":/new/images/rule.png");
    //pen.drawImage(640,217,images);
    QPixmap pix;
    pix.load(":/images/rule.jpg");
    pen.drawPixmap(0,0,696,647,pix);//绝对位置：（640,217）
    update();
}

void Rule::paintEvent(QPaintEvent*w)
{
    Q_UNUSED(w);
    QPainter pen(this);
    pen.drawPixmap(0,0,maptemp);
}

void Rule::closeThis()
{
    this->close();
}

Rule::~Rule()
{
    delete ui;
}
