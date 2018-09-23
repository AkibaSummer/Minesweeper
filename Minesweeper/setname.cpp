#include "setname.h"
#include "ui_setname.h"
extern QString name_;
extern int status_;
extern int difficulty_;
extern int score_;

SetName::SetName(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetName)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//隐藏边栏
    this->setWindowModality(Qt::ApplicationModal);//阻塞其他窗口

    connect(ui->btn_enter,SIGNAL(clicked(bool)),this,SLOT(enterName()));
}
void SetName::paintEvent(QPaintEvent*w)
{
    Q_UNUSED(w);
    QPainter pen(this);
    QImage image(":/images/inputName.jpg");
    pen.drawImage(0,0,image);
}

/*void SetName::mousePressEvent(QMouseEvent*m)
{
    int x=m->x();
    int y=m->y();
    if(x>=160&&x<=240&&y>=170&&y<=190){
    }
}
*/
/*void SetName::getInfo(int status,int difficulty,int score)
{
    name_="sb";
    e.init(status,difficulty,name_,score);
}
*/
void SetName::enterName(){
    name_=ui->line_name->text();
    //QPixmap pix(&);
    //pix.load(":/images/inputName.jpg");
    //pix.drawPixmap(0,0,);
    endw.show();
    endw.init();
    this->close();
}

SetName::~SetName(){
    delete ui;
}
