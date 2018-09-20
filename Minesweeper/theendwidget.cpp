#include "theendwidget.h"
#include "ui_theendwidget.h"
#include <qlabel.h>
#include <QString>
#include <qfile.h>
#include "game.h"
#include <QPixmap>
#include <QImage>
#include "rank.h"
extern vector<Player> easPlLi;	//简单成绩列表
extern vector<Player> midPlLi;	//中等成绩列表
extern vector<Player> difPlLi;	//困难成绩列表
extern vector<Player> cosPlLi;	//自定成绩列表
extern QString name_;
extern int status_;
extern int difficulty_;
extern int score_;

TheEndWidget::TheEndWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TheEndWidget)
{
    init();
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//隐藏边栏
    this->setWindowModality(Qt::ApplicationModal);//阻塞其他窗口
}

void TheEndWidget::init()
{
    maps.status=status_;
    if(maps.status==1){
        images.load(":/images/victory.jpg");
        QPainter pen(&maptemp);
        images=images.scaled(685,633,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        pen.drawImage(0,0,images);}//画入背景图片//如果玩家赢得游戏，显示为胜利界面
   else if(maps.status==-1) {
        images.load(":/images/defeat.jpg");
        QPainter pen(&maptemp);
        images=images.scaled(685,633,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        pen.drawImage(0,0,images);}//若果游戏失败，显示失败界面
    inlabel(difficulty_,name_,score_);
}

void TheEndWidget::paintEvent(QPaintEvent*w){
    Q_UNUSED(w);
    QPainter pen(this);
    pen.drawPixmap(0,0,maptemp);
}

QString sp(int n){
    QString s;
    for (int i=1;i<=n;i++){
        s=s+' ';
    }
    return s;
}

void TheEndWidget::inlabel(int difficulty,QString name,int score)//排行榜文件里面是名次，人名，分数
{
    name=name_;
    QString string[10];//定义一个数组，存取排行榜文件中的内容    如何获取难度？？
    vector<Player> str;
    Player pla;
    Ranking ran;
    newRank.init();
    ran=newRank.setInfo(difficulty,name,score);
    str=ran.allRank_;
    pla=ran.curRank_;
    switch(difficulty){

    case 1: {
        ui->label->setText("Easy");
        for(unsigned int i=0;i<str.size()&&i<10;i++){
            int space1=8-QString::number(str[i].ranking_).size();
            int space2=10-str[i].player_.size();

            string[i]="  "+QString::number(str[i].ranking_) ;
            string[i]+=sp(space1);
            string[i]+= str[i].player_;
            string[i]+=sp(space2);
            string[i]+=QString::number( str[i].score_) ;
        }
        ui->label_1->setText(string[0]);
        ui->label_2->setText(string[1]);
        ui->label_3->setText(string[2]);
        ui->label_4->setText(string[3]);
        ui->label_5->setText(string[4]);
        ui->label_6->setText(string[5]);
        ui->label_7->setText(string[6]);
        //将文件中的内容输出到label上
        break;
    }
     case 2:{
        ui->label->setText("Common");
        for(unsigned int i=0;i<str.size()&&i<10;i++){
            int space1=8-QString::number(str[i].ranking_).size();
            int space2=10-str[i].player_.size();

            string[i]="  "+QString::number(str[i].ranking_) ;
            string[i]+=sp(space1);
            string[i]+= str[i].player_;
            string[i]+=sp(space2);
            string[i]+=QString::number( str[i].score_) ;}
        ui->label_1->setText(string[0]);
        ui->label_2->setText(string[1]);
        ui->label_3->setText(string[2]);
        ui->label_4->setText(string[3]);
        ui->label_5->setText(string[4]);
        ui->label_6->setText(string[5]);
        ui->label_7->setText(string[6]);
      //将文件中的内容输出到label上
        break;}

     case 3:{
        ui->label->setText("Master");
        for(unsigned int i=0;i<str.size()&&i<10;i++){
            int space1=8-QString::number(str[i].ranking_).size();
            int space2=10-str[i].player_.size();

            string[i]="  "+QString::number(str[i].ranking_) ;
            string[i]+=sp(space1);
            string[i]+= str[i].player_;
            string[i]+=sp(space2);
            string[i]+=QString::number( str[i].score_) ;}
        ui->label_1->setText(string[0]);
        ui->label_2->setText(string[1]);
        ui->label_3->setText(string[2]);
        ui->label_4->setText(string[3]);
        ui->label_5->setText(string[4]);
        ui->label_6->setText(string[5]);
        ui->label_7->setText(string[6]);
      //将文件中的内容输出到label上
        break; }
     case 4:{
        ui->label->setText("Custom");
        for(unsigned int i=0;i<str.size()&&i<10;i++){
            int space1=8-QString::number(str[i].ranking_).size();
            int space2=10-str[i].player_.size();

            string[i]="  "+QString::number(str[i].ranking_) ;
            string[i]+=sp(space1);
            string[i]+= str[i].player_;
            string[i]+=sp(space2);
            string[i]+=QString::number( str[i].score_) ;
        }
        ui->label_1->setText(string[0]);
        ui->label_2->setText(string[1]);
        ui->label_3->setText(string[2]);
        ui->label_4->setText(string[3]);
        ui->label_5->setText(string[4]);
        ui->label_6->setText(string[5]);
        ui->label_7->setText(string[6]);
        //将文件中的内容输出到label上
        break;

    }

    }
    if(status_==1){
        int space1=8-QString::number(pla.ranking_).size();
        int space2=10-pla.player_.size();
        string[7]="  "+QString::number(pla.ranking_);
        string[7]+= sp(space1);
        string[7]+=pla.player_;
        string[7]+=sp(space2);
        string[7]+=  QString::number(pla.score_);
        ui->label_8->setText(string[7]);
    }//如果赢了，则第八行输出玩家自己的成绩
   else if(status_==-1)ui->label_8->setText(string[7]);//如果输了，仍输出排行榜文件中的第八名
}
void TheEndWidget::on_pushButton_clicked()//重新开始此轮游戏
{
    newGame.reset();
}

void TheEndWidget::on_pushButton_2_clicked()//再来一轮新游戏
{   int mineNumber=10;//需要在之前获得
    int seed=time(0);//
    newGame.init(newGame.maps.size(),newGame.maps.front().size(),mineNumber,seed);
    //newGame为用户玩的那一局的game的对象
}

void TheEndWidget::on_pushButton_3_clicked()//返回菜单
{
    this->close();
}


TheEndWidget::~TheEndWidget()
{
    delete ui;
}
