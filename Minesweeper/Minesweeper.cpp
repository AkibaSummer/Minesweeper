#include "Minesweeper.h"
#include<QDebug>
#ifdef _WIN32
#include "Windows.h"
#include <synchapi.h>
#include <QFileInfo>
#endif
extern vector<Player> easPlLi;	//简单成绩列表
extern vector<Player> midPlLi;	//中等成绩列表
extern vector<Player> difPlLi;	//困难成绩列表
extern vector<Player> cosPlLi;	//自定成绩列表
extern int status_;
extern int difficulty_;
extern int score_;
const int songtime=(3*60+16)*5*1000;
extern QMediaPlayer *myPlayer;
extern void jinrumusicstop();

Minesweeper::Minesweeper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Minesweeper)
{
    ui->setupUi(this);

    ra.init();
    theme=1;
    this->pTimer=new QTimer;//计时器
    connect(this->pTimer,SIGNAL(timeout()),this,SLOT(updateTimeAndDisplay()));//如果溢出就自动更新时间

    disconnect(&endw,SIGNAL(on_pushButton_clickeds()),this,SLOT(restart()));
    connect(&endw,SIGNAL(on_pushButton_clickeds()),this,SLOT(restart()));

    disconnect(&endw,SIGNAL(on_pushButton_2_clickeds()),this,SLOT(restartNew()));
    connect(&endw,SIGNAL(on_pushButton_2_clickeds()),this,SLOT(restartNew()));

    disconnect(&endw,SIGNAL(on_pushButton_3_clickeds()),this,SLOT(backToMenu()));
    connect(&endw,SIGNAL(on_pushButton_3_clickeds()),this,SLOT(backToMenu()));

    disconnect(&setName.endw,SIGNAL(on_pushButton_clickeds()),this,SLOT(restart()));
    connect(&setName.endw,SIGNAL(on_pushButton_clickeds()),this,SLOT(restart()));

    disconnect(&setName.endw,SIGNAL(on_pushButton_2_clickeds()),this,SLOT(restartNew()));
    connect(&setName.endw,SIGNAL(on_pushButton_2_clickeds()),this,SLOT(restartNew()));

    disconnect(&setName.endw,SIGNAL(on_pushButton_3_clickeds()),this,SLOT(backToMenu()));
    connect(&setName.endw,SIGNAL(on_pushButton_3_clickeds()),this,SLOT(backToMenu()));


    ui->le_ea_1->setText(getInfo(1,1));
    ui->le_ea_2->setText(getInfo(1,2));
    ui->le_ea_3->setText(getInfo(1,3));
    ui->le_ea_4->setText(getInfo(1,4));
    ui->le_ea_5->setText(getInfo(1,5));

    ui->le_mi_1->setText(getInfo(2,1));
    ui->le_mi_2->setText(getInfo(2,2));
    ui->le_mi_3->setText(getInfo(2,3));
    ui->le_mi_4->setText(getInfo(2,4));
    ui->le_mi_5->setText(getInfo(2,5));
    ui->le_mi_6->setText(getInfo(2,6));

    ui->le_zz_1->setText(getInfo(3,1));
    ui->le_zz_2->setText(getInfo(3,2));
    ui->le_zz_3->setText(getInfo(3,3));
    ui->le_zz_4->setText(getInfo(3,4));
    ui->le_zz_5->setText(getInfo(3,5));
    ui->le_zz_6->setText(getInfo(3,6));
    \
    jinrumusic();
    timer->disconnect();
    timer->stop();
    connect(timer, SIGNAL(timeout()), this, SLOT(jinrumusic()));
    timer->start(songtime);

    init();
    //this->setWindowOpacity(0);  //设置窗口透明度
}

void Minesweeper::init()
{
    ui->lcdNumber->setVisible(0);//一开始不显示lcdnumber计时器
    QPainter painter(&maptemp);
    painter.drawPixmap(0,0,1920,1080,img.img_U);//直接加载绿色背景图
}

void Minesweeper::paintEvent(QPaintEvent*w)
{
    Q_UNUSED(w);
    QPainter pen(this);
    pen.drawPixmap(0,0,maptemp);
}

QString Minesweeper::sp(int n){
    QString s;
    for (int i=1;i<=n;i++){
        s=s+' ';
    }
    return s;
}

QString Minesweeper::getInfo(int dif,unsigned int num)
{
    QString player;
    if(1==dif){
        int space_1=6-QString::number(easPlLi[num-1].ranking_).size();
        int space_2=20-easPlLi[num-1].player_.size();
        player="  "+QString::number(easPlLi[num-1].ranking_)+sp(space_1)+easPlLi[num-1].player_+sp(space_2)+QString::number(easPlLi[num-1].score_);
        return player;
    }else if(2==dif){
        int space_1=6-QString::number(midPlLi[num-1].ranking_).size();
        int space_2=20-midPlLi[num-1].player_.size();
        player="  "+QString::number(midPlLi[num-1].ranking_)+sp(space_1)+midPlLi[num-1].player_+sp(space_2)+QString::number(midPlLi[num-1].score_);
        return player;
    }else if(3==dif){
        int space_1=6-QString::number(difPlLi[num-1].ranking_).size();
        int space_2=20-difPlLi[num-1].player_.size();
        player="  "+QString::number(difPlLi[num-1].ranking_)+sp(space_1)+difPlLi[num-1].player_+sp(space_2)+QString::number(difPlLi[num-1].score_);
        return player;
    }else if(4==dif){
        int space_1=6-QString::number(cosPlLi[num-1].ranking_).size();
        int space_2=20-cosPlLi[num-1].player_.size();
        player="  "+QString::number(cosPlLi[num-1].ranking_)+sp(space_1)+cosPlLi[num-1].player_+sp(space_2)+QString::number(cosPlLi[num-1].score_);
        return player;
    }else{
        player="null";
        return player;
    }
}

void Minesweeper::showTime()//这是触发计时器开始的函数
{
    this->baseTime=QTime::currentTime();//获取当前时间
    this->pTimer->start(1);//将当前的系统时间设置为1
}

void Minesweeper::updateTimeAndDisplay(){//更新时间的槽函数
    QTime current = QTime::currentTime();//currentTime函数返回当前时间
    t = this->baseTime.msecsTo(current)/1000;//把当前时间转化为ms，其实t就记录了过去的时间
    QTime showTime(0,0,0,0);//构造一个对象是00：00
    showTime = showTime.addMSecs(t*1000);//返回一个ms差，就可以将这个QTime对象本身用于存储流逝的时间
    QString showStr=showTime.toString("mm:ss");//用分秒的形式处理转换为QString
    this->ui->lcdNumber->display(showStr);//用lcdNumbe展示
}

void Minesweeper::restart(){
    loc = 2;

    pTimer->stop();//停止计时
    game.setBack();//先将所有的属性置为原来的然后调用绘制
    clickTimes = 0;
    ui->lcdNumber->display("00:00");
    game.score = 0;
    drawGame();
}
void Minesweeper::restartNew(){
    loc = 2;
    pTimer->stop();//停止计时
    clickTimes = 0;//设置可以显示时间
    game.score = 0;
    loadGame(diff,game.size_x,game.size_y,game.totalNum);//再重新绘制本难度的地图,但是雷的数量会出问题
}

void Minesweeper::backToMenu(){
    ra.init();
    ui->le_ea_1->setText(getInfo(1,1));
    ui->le_ea_2->setText(getInfo(1,2));
    ui->le_ea_3->setText(getInfo(1,3));
    ui->le_ea_4->setText(getInfo(1,4));
    ui->le_ea_5->setText(getInfo(1,5));

    ui->le_mi_1->setText(getInfo(2,1));
    ui->le_mi_2->setText(getInfo(2,2));
    ui->le_mi_3->setText(getInfo(2,3));
    ui->le_mi_4->setText(getInfo(2,4));
    ui->le_mi_5->setText(getInfo(2,5));
    ui->le_mi_6->setText(getInfo(2,6));

    ui->le_zz_1->setText(getInfo(3,1));
    ui->le_zz_2->setText(getInfo(3,2));
    ui->le_zz_3->setText(getInfo(3,3));
    ui->le_zz_4->setText(getInfo(3,4));
    ui->le_zz_5->setText(getInfo(3,5));
    ui->le_zz_6->setText(getInfo(3,6));
    ui->label->setVisible(1);
    ui->le_ea_1->setVisible(1);
    ui->le_ea_2->setVisible(1);
    ui->le_ea_3->setVisible(1);
    ui->le_ea_4->setVisible(1);
    ui->le_ea_5->setVisible(1);
    ui->le_mi_1->setVisible(1);
    ui->le_mi_2->setVisible(1);
    ui->le_mi_3->setVisible(1);
    ui->le_mi_4->setVisible(1);
    ui->le_mi_5->setVisible(1);
    ui->le_mi_6->setVisible(1);
    ui->le_zz_1->setVisible(1);
    ui->le_zz_2->setVisible(1);
    ui->le_zz_3->setVisible(1);
    ui->le_zz_4->setVisible(1);
    ui->le_zz_5->setVisible(1);
    ui->le_zz_6->setVisible(1);
    loc = 1;//返回开始界面
   // startMusic();

    pTimer->stop();//返回以后也要停止计时
    clickTimes = 0;
    init();//重新绘制开始界面后面的背景
    ui->labelMode->setVisible(0);//模式
    ui->lcdNumber->setVisible(0);//计时器
    pTimer->stop();//停止计时
    ui->labelMine->setVisible(0);//雷数
    ui->label->setVisible(1);//把label那张png设为可见的
    //返回菜单以后还要把当前的游戏结束，界面内容全都清除，以及雷数设置为动态的
}

void Minesweeper::mousePressEvent(QMouseEvent*m)
{
    int x=m->x();
    int y=m->y();
    if (loc==1){//main
        if(m->button()==Qt::LeftButton){
            if(x>=1243&&x<=1462&&y>=149&&y<=939){       //海洋
                theme=1;
                startMusic();
                res={
                    ":/images/Sea/01.png",
                    ":/images/Sea/04.png",
                    ":/images/Sea/05.jpg",
                    ":/images/Sea/14.jpg",
                    ":/images/Sea/15.jpg",
                    ":/images/Sea/gameBack.png",
                    ":/images/Sea/menu1.jpg",
                    ":/images/Sea/U1.jpg"
                };
                changeBackGround(":/images/U1.png");
            }
            else if(x>=1462&&x<=1696&&y>=149&&y<=860){ //冰川
                theme=2;
                startMusic();
                res={
                    ":/images/Glacier/01.jpg",
                    ":/images/Glacier/04.png",
                    ":/images/Glacier/05.jpg",
                    ":/images/Glacier/14.jpg",
                    ":/images/Glacier/15.jpg",
                    ":/images/Glacier/gameBack.png",
                    ":/images/Glacier/menu2.jpg",
                    ":/images/Glacier/U2.jpg"
                };
                changeBackGround(":/images/U2.png");
            }
            else if(x>=1701&&x<=1890&&y>=149&&y<=778){ //动漫
                theme=3;
                startMusic();
                res={
                    "",
                    ":/images/Anime/04.png",
                    ":/images/Anime/05.jpg",
                    ":/images/Anime/14.jpg",
                    ":/images/Anime/15.jpg",
                    ":/images/Anime/gameBack.png",
                    ":/images/Anime/menu3.jpg",
                    ":/images/Anime/U3.jpg"
                };
                changeBackGround(":/images/U3.png");
            }
            else if(x>=685&&x<=1181&&y>=67&&y<=267){   //简单
                //jinrumusicstop();
                //startMusic();
                res.level = "Easy";
                loadGame(1,8,8,8);//先加载游戏
                repaint();
            }
            else if(x>=685&&x<=1181&&y>=270&&y<=470){  //中等
                //jinrumusicstop();
                //startMusic();
                res.level = "Common";
                loadGame(2,18,18,50);
                repaint();
            }
            else if(x>=685&&x<=1181&&y>=473&&y<=673){  //大师
                //jinrumusicstop();
                //startMusic();
                res.level = "Master";
                loadGame(3,28,28,122);
                repaint();
            }
            else if(x>=685&&x<=1181&&y>=676&&y<=876){  //自定义
                res.level = "Custom";
                customOfGame();
            }
            else if(x>=685&&x<=1181&&y>=879&&y<=1079){ //游戏规则
                ruleOfGame();
            }
            else if(x>=1843&&x<=1920&&y>=0&&y<=78){
                closeThis();
            }
            else{
                update();
            }
        }
    }

    else if(loc==2){//game界面
        ui->lcdNumber->setVisible(1);//只要在游戏界面就显示计时器
        int clickX(-1),clickY(-1);
        int blockSizeX=1000/game.size_x;
        int blockSizeY=1000/game.size_y;
        blockSizeX=blockSizeY=min(blockSizeX,blockSizeY);
        if(x>=120&&x<=373&&y>=636&&y<=761){//再玩一局
            restartNew();
        }
        else if(x>=120&&x<=373&&y>=767&&y<=909){//重玩本局
            restart();
        }
        else if(x>=1707&&x<=1862&&y>=905&&y<=1018){
            backToMenu();
        }
        for (int i=0;i<game.size_x;i++){
            for (int j=0;j<game.size_y;j++){
                if (x>=centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12&&
                        y>=centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12&&
                        x<=centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12+blockSizeX-4&&
                        y<=centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12+blockSizeY-4){
                    clickX=i;clickY=j;
                    break;
                }
            }
            if (clickX+clickY!=-2)break;
        }
        if (clickX+clickY!=-2){
            if(!clickTimes)showTime();
            if(m->button()==Qt::LeftButton&&m->button()==Qt::RightButton){
                clickTimes = 1;//标志用来判断是否第二次点击,clickX跟y以后没有用了
                if((game.tag = game.doubleClick(clickX,clickY).status)){//判断返回值是否为1或者-1
                    drawGame();
                    pTimer->stop();
                    if(game.tag == 1){
                        if(res.level == "Easy"){
                            game.score = 10000.0/(double)t;//计算分数
                            status_=game.tag;
                            difficulty_=1;
                            score_=game.score;
                            setName.show();
                            //弹出界面
                        }
                        else if(res.level == "Common"){
                            game.score = 100000.0/(double)t;
                            status_=game.tag;
                            difficulty_=2;
                            score_=game.score;
                            setName.show();
                            //弹出界面
                        }
                        else if(res.level == "Master"){
                            game.score = 1000000.0/(double)t;
                            status_=game.tag;
                            difficulty_=3;
                            score_=game.score;
                            setName.show();
                            //弹出界面
                        }
                        else if(res.level == "Custom"){
                            qDebug()<<game.totalNum;
                            game.score = 10000.0*(double)game.totalNum*game.totalNum/t/game.size_x/game.size_y;

                            qDebug()<<game.score;
                            status_=game.tag;
                            difficulty_=4;
                            score_=game.score;
                            setName.show();
                            //弹出界面
                        }
                    }
                    else {//else 绘制界面
                        if(res.level == "Easy"){
                            score_=0;
                            status_=-1;
                            difficulty_=1;
                            endw.show();
                            endw.init();
                            //弹出界面
                        }
                        else if(res.level == "Common"){
                            score_=0;
                            status_=-1;
                            difficulty_=2;
                            endw.show();
                            endw.init();                           //弹出界面
                        }
                        else if(res.level == "Master"){
                            score_=0;
                            status_=-1;
                            difficulty_=3;
                            endw.show();
                            endw.init();                        }
                        else if(res.level == "Custom"){
                            score_=0;
                            status_=-1;
                            difficulty_=4;
                            endw.show();
                            endw.init();                        }
                    }
                }
                else drawGame();//若返回值为0则继续游戏
            }
            else if(m->button()==Qt::LeftButton){//接收到左键单击
                clickTimes = 1;
                if((game.tag = game.leftClick(clickX,clickY).status)){//判断返回值是否为1或者-1
                    drawGame();


                    pTimer->stop();
                    if(game.tag == 1){
                        if(res.level == "Easy"){
                            game.score = 10000.0/(double)t;//计算分数
                            status_=game.tag;
                            difficulty_=1;
                            score_=game.score;
                            setName.show();//弹出界面
                        }
                        else if(res.level == "Common"){
                            game.score = 100000.0/(double)t;
                            status_=game.tag;
                            difficulty_=2;
                            score_=game.score;
                            setName.show();//弹出界面
                        }
                        else if(res.level == "Master"){
                            game.score = 1000000.0/(double)t;
                            status_=game.tag;
                            difficulty_=3;
                            score_=game.score;
                            setName.show();//弹出界面
                        }
                        else if(res.level == "Custom"){
                            game.score = 10000.0*(double)game.totalNum*game.totalNum/t/game.size_x/game.size_y;
                            status_=game.tag;
                            difficulty_=4;
                            score_=game.score;
                            setName.show();
                        }
                    }
                    else {//else 绘制界面
                        QMediaPlayer *myPlayer= new QMediaPlayer;
                        myPlayer->setMedia(QUrl::fromLocalFile("D:/Ddocuments/Minesweeper8.1.0/Minesweeper8.1.0/Sound/boom.mp3"));
                        myPlayer->setVolume(80);
                        myPlayer->play();
                        if(res.level == "Easy"){
                            score_=0;
                            status_=-1;
                            difficulty_=1;
                            endw.show();
                            endw.init();//弹出界面
                        }
                        else if(res.level == "Common"){
                            score_=0;
                            status_=-1;
                            difficulty_=2;
                            endw.show();
                            endw.init();                            //ui->labelScore->setText(QString::number(game.score));//弹出界面
                        }
                        else if(res.level == "Master"){
                            score_=0;
                            status_=-1;
                            difficulty_=3;
                            endw.show();
                            endw.init();                        }
                        else if(res.level == "Custom"){
                            score_=0;
                            status_=-1;
                            difficulty_=4;
                            endw.show();
                            endw.init();                        }
                    }                    clickTimes = 0;
                }
                else drawGame();//若返回值为0则继续游戏

                QMediaPlayer *myPlayer= new QMediaPlayer;
                myPlayer->setMedia(QUrl::fromLocalFile("D:/Ddocuments/Minesweeper8.1.0/Minesweeper8.1.0/Sound/anjian/clickleft.mp3"));
                myPlayer->setVolume(80);
                myPlayer->play();
            }
            else if(m->button()==Qt::RightButton){//右键单击
                clickTimes = 1;
                if((game.tag = game.rightClick(clickX,clickY).status)){//判断返回值是否为1或者-1
                    drawGame();
                    pTimer->stop();
                    if(game.tag == 1){
                        if(res.level == "Easy"){
                            game.score = 10000.0/(double)t;//计算分数
                            status_=game.tag;
                            difficulty_=1;
                            score_=game.score;
                            setName.show();//弹出界面
                        }
                        else if(res.level == "Common"){
                            game.score = 100000.0/(double)t;
                            status_=game.tag;
                            difficulty_=2;
                            score_=game.score;
                            setName.show();//弹出界面
                        }
                        else if(res.level == "Master"){
                            game.score = 1000000.0/(double)t;
                            status_=game.tag;
                            difficulty_=3;
                            score_=game.score;
                            setName.show();//弹出界面
                        }
                        else if(res.level == "Custom"){
                            game.score = 10000.0*(double)game.totalNum*game.totalNum/t/game.size_x/game.size_y;
                            status_=game.tag;
                            difficulty_=4;
                            score_=game.score;
                            setName.show();
                        }
                    }
                    else {//else 绘制界面
                        QMediaPlayer *myPlayer= new QMediaPlayer;
                        myPlayer->setMedia(QUrl::fromLocalFile("D:/Ddocuments/Minesweeper8.1.0/Minesweeper8.1.0/Sound/boom.mp3"));//炸弹声
                        myPlayer->setVolume(80);
                        myPlayer->play();
                        if(res.level == "Easy"){
                            score_=0;
                            status_=-1;
                            difficulty_=1;
                            endw.show();
                            endw.init();
                           //弹出界面
                        }
                        else if(res.level == "Common"){
                            score_=0;
                            status_=-1;
                            difficulty_=2;
                            endw.show();
                            endw.init();                            //弹出界面
                        }
                        else if(res.level == "Master"){
                            score_=0;
                            status_=-1;
                            difficulty_=3;
                            endw.show();
                            endw.init();                        }
                        else if(res.level == "Custom"){
                            score_=0;
                            status_=-1;
                            difficulty_=4;
                            endw.show();
                            endw.init();                        }
                    }                    clickTimes = 0;
                }
                else drawGame();//若返回值为0则继续游戏
                QMediaPlayer *myPlayer= new QMediaPlayer;
                myPlayer->setMedia(QUrl::fromLocalFile("D:/Ddocuments/Minesweeper8.1.0/Minesweeper8.1.0/Sound/anjian/clickright.mp3"));//点击的按键声音
                myPlayer->setVolume(80);
                myPlayer->play();
            }

        }
    }
}


void Minesweeper::mouseDoubleClickEvent(QMouseEvent*m)
{
    int x=m->x();
    int y=m->y();
    if(loc==2){//game
        int clickX(-1),clickY(-1);
        int blockSizeX=1000/game.size_x;
        int blockSizeY=1000/game.size_y;
        blockSizeX=blockSizeY=min(blockSizeX,blockSizeY);
        if((clickX+clickY == -2)&&(clickTimes == 0))
            showTime();
        for (int i=0;i<game.size_x;i++){
            for (int j=0;j<game.size_y;j++){
                if (x>=centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12&&
                        y>=centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12&&
                        x<=centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12+blockSizeX-4&&
                        y<=centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12+blockSizeY-4){
                    clickX=i;clickY=j;
                    break;
                }
            }
            if (clickX+clickY!=-2)
                break;
        }
        if (clickX+clickY!=-2){
            //game.doubleClick(clickX,clickY);
            if((game.tag = game.doubleClick(clickX,clickY).status)){//判断返回值是否为1或者-1
                clickTimes = 1;//
                drawGame();
                pTimer->stop();
                if(game.tag == 1){
                    if(res.level == "Easy"){
                        game.score = 10000.0/(double)t;//计算分数
                        status_=game.tag;
                        difficulty_=1;
                        score_=game.score;
                        setName.show();
                       //弹出界面
                    }
                    else if(res.level == "Common"){
                        game.score = 100000.0/(double)t;
                        status_=game.tag;
                        difficulty_=2;
                        score_=game.score;
                        setName.show();
                        //ui->labelScore->setText(QString::number(game.score));//弹出界面
                    }
                    else if(res.level == "Master"){
                        game.score = 1000000.0/(double)t;
                        status_=game.tag;
                        difficulty_=3;
                        score_=game.score;
                        setName.show();
                        //弹出界面
                    }
                    else if(res.level == "Custom"){

                        game.score = 10000.0*(double)game.totalNum*game.totalNum/t/game.size_x/game.size_y;
                        status_=game.tag;
                        difficulty_=4;
                        score_=game.score;
                        setName.show();
                    }
                    clickTimes = 0;
                }
                else {//else 绘制界面
                    QMediaPlayer *myPlayer= new QMediaPlayer;
                    myPlayer->setMedia(QUrl::fromLocalFile("D:/Ddocuments/Minesweeper8.1.0/Minesweeper8.1.0/Sound/boom.mp3"));//设置炸弹爆炸的声音
                    myPlayer->setVolume(80);
                    myPlayer->play();
                    if(res.level == "Easy"){
                        score_=0;
                        status_=-1;
                        difficulty_=1;
                        endw.show();
                        endw.init();
                        //ui->labelScore->setText(QString::number(game.score));//弹出界面
                    }
                    else if(res.level == "Common"){
                        score_=0;
                        status_=-1;
                        difficulty_=2;
                        endw.show();
                        endw.init();                       //弹出界面
                    }
                    else if(res.level == "Master"){
                        score_=0;
                        status_=-1;
                        difficulty_=3;
                        endw.show();
                        endw.init();                        }
                    else if(res.level == "Custom"){
                        score_=0;
                        status_=-1;
                        difficulty_=4;
                        endw.show();
                        endw.init();                        }
                }
            }
            else drawGame();//若返回值为0则继续游戏
        }
    }
}

void Minesweeper::ruleOfGame()
{
    QMediaPlayer *myPlayer= new QMediaPlayer;
    myPlayer->setMedia(QUrl::fromLocalFile("D:/Ddocuments/Minesweeper8.1.0/Minesweeper8.1.0/Sound/qiehuang.mp3"));//设置切换的声音
    myPlayer->setVolume(80);
    myPlayer->play();
    ru.show();
}

void Minesweeper::customOfGame()
{
    QMediaPlayer *myPlayer= new QMediaPlayer;
    myPlayer->setMedia(QUrl::fromLocalFile("D:/Ddocuments/Minesweeper8.1.0/Minesweeper8.1.0/Sound/qiehuang.mp3"));//设置切换的声音
    myPlayer->setVolume(80);
    myPlayer->play();
    cu.show();
    disconnect(&cu,SIGNAL(setCustomInfo(int,int,int,int)),this,SLOT(setCustomGame(int,int,int,int)));
    connect(&cu,SIGNAL(setCustomInfo(int,int,int,int)),this,SLOT(setCustomGame(int,int,int,int)));
}

void Minesweeper::changeBackGround(QString picDir)
{
    QPainter painter(&maptemp);
    pix.load(picDir);
    for(int i=0;i<20;i++){
        painter.drawPixmap(0,0,1920,1080,pix);
#ifdef __linux__
        system("sleep 0.001");
#elif _WIN32
        Sleep(1);
#endif
        repaint();
    }
    //pix.load(picDir+".jpg");
    //painter.drawPixmap(0,0,1920,1080,pix);
    //repaint();
}


void Minesweeper::loadGame(int _diff,int x,int y ,int num){//diff x y num
    ui->label->setVisible(0);
    ui->le_ea_1->setVisible(0);
    ui->le_ea_2->setVisible(0);
    ui->le_ea_3->setVisible(0);
    ui->le_ea_4->setVisible(0);
    ui->le_ea_5->setVisible(0);
    ui->le_mi_1->setVisible(0);
    ui->le_mi_2->setVisible(0);
    ui->le_mi_3->setVisible(0);
    ui->le_mi_4->setVisible(0);
    ui->le_mi_5->setVisible(0);
    ui->le_mi_6->setVisible(0);
    ui->le_zz_1->setVisible(0);
    ui->le_zz_2->setVisible(0);
    ui->le_zz_3->setVisible(0);
    ui->le_zz_4->setVisible(0);
    ui->le_zz_5->setVisible(0);
    ui->le_zz_6->setVisible(0);

    ui->labelMode->setVisible(1);//设置菜单栏各个label\计时器可见
    ui->lcdNumber->setVisible(1);
    ui->labelMine->setVisible(1);
    ui->labelMode->setText(res.level);
    ui->lcdNumber->display("00:00");
    diff=_diff;//diff保持不变除非重新点击开始界面的按钮
    loc=2;
    game.init(x,y,num,time(0));
    //    QPixmap img_01;
    //    QPixmap img_04;
    //    QPixmap img_05;
    //    QPixmap img_14;
    //    QPixmap img_15;
    //    QPixmap img_gameBack;
    //    QPixmap img_menu;
    //    QPixmap img_U;
    //    QPixmap img_0201;
    //    QPixmap img_0202;
    //    QPixmap img_0203;
    //    QPixmap img_0204;
    //    QPixmap img_0205;
    //    QPixmap img_0206;
    //    QPixmap img_0207;
    //    QPixmap img_0208;
    //    QPixmap img_03;
    //    QPixmap img_11;
    int blockSizeX=1000/game.size_x;
    int blockSizeY=1000/game.size_y;
    blockSizeX=blockSizeY=min(blockSizeX,blockSizeY);
    img.img_U.load(res.img_U);
    img.img_01.load(res.img_01);
    img.img_04.load(res.img_04);
    img.img_05.load(res.img_05);
    img.img_14.load(res.img_14);
    img.img_15.load(res.img_15);
    img.img_gameBack.load(res.img_gameBack);
    img.img_01=img.img_01.scaled(blockSizeX-4,blockSizeY-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    img.img_04=img.img_04.scaled(blockSizeX-4,blockSizeY-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    img.img_05=img.img_05.scaled(blockSizeX-4,blockSizeY-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    img.img_14=img.img_14.scaled(blockSizeX-4,blockSizeY-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    img.img_15=img.img_15.scaled(blockSizeX-4,blockSizeY-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    img.img_gameBack=img.img_gameBack.scaled(blockSizeX*game.size_x+20,blockSizeY*game.size_y+20,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    //img.img_menu=img.img_menu.scaled();
    //img.img_U=img.img_U.scaled(1920,1080);
    img.img_0201=img.img_0201.scaled(blockSizeX-4,blockSizeY-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    img.img_0202=img.img_0202.scaled(blockSizeX-4,blockSizeY-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    img.img_0203=img.img_0203.scaled(blockSizeX-4,blockSizeY-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    img.img_0204=img.img_0204.scaled(blockSizeX-4,blockSizeY-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    img.img_0205=img.img_0205.scaled(blockSizeX-4,blockSizeY-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    img.img_0206=img.img_0206.scaled(blockSizeX-4,blockSizeY-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    img.img_0207=img.img_0207.scaled(blockSizeX-4,blockSizeY-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    img.img_0208=img.img_0208.scaled(blockSizeX-4,blockSizeY-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    img.img_03=img.img_03.scaled(blockSizeX-4,blockSizeY-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    //img.img_11=img.img_11.scaled(blockSizeX-4,blockSizeY-4);
    drawGame();//在loadGame里进行第一级加载游戏

}

void Minesweeper::drawGame(){
    QPainter painter(&maptemp);
    painter.drawPixmap(0,0,img.img_U);//画背景
    pix1.load(res.img_menu);
    painter.drawPixmap(120,186,253,737,pix1);//画菜单栏
    pix2.load(":/images/11.png");
    painter.drawPixmap(1707,905,155,113,pix2);//返回主菜单的按键
    ui->labelMine->setText(QString::number(game.boomNum));//game.init里面有东西传入以后才能对mine的数量进行初始化
    //if(clickTimes == 1)
    //   showTime();//启动计时器

    int blockSizeX=1000/game.size_x;
    int blockSizeY=1000/game.size_y;
    blockSizeX=blockSizeY=min(blockSizeX,blockSizeY);
    painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2,centerY-(blockSizeY*game.size_y+20)/2,img.img_gameBack);
    for (int i=0;i<game.size_x;i++){
        for (int j=0;j<game.size_y;j++){
            switch (game.getMaps().getMapStatus()[i][j]){
            case 9:
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_01);
                break;
            case 10:
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_01);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_03);
                break;
            case 11:
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,blockSizeX-4,blockSizeY-4,img.img_14);
                break;
            case 12:
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_14);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_04);
                break;
            case 13:
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_14);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_05);
                break;
            case 1:
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_01);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_0201);
                break;
            case 2:
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_01);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_0202);
                break;
            case 3:
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_01);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_0203);
                break;
            case 4:
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_01);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_0204);
                break;
            case 5:
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_01);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_0205);
                break;
            case 6:
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_01);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_0206);
                break;
            case 7:
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_01);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_0207);
                break;
            case 8:
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_01);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,img.img_0208);
                break;
            default:
                break;
            }
        }
    }
    repaint();

}

void Minesweeper::closeThis()
{
    this->close();
}

void Minesweeper::setCustomGame(int diff,int x,int y,int num){
    if (num>=8&&num<=(x-1)*(y-1))
        loadGame(diff ,x,y,num);
}
Minesweeper::~Minesweeper()
{
    delete ui;
}

void Minesweeper::jinrumusic(){
    myPlayer->setMedia(QUrl::fromLocalFile("D:/Ddocuments/Minesweeper8.1.0/Minesweeper8.1.0/Sound/wang.mp3"));
    myPlayer->setVolume(80);//D:/Ddocuments/Minesweeper8.1.0/Minesweeper8.1.0是本地路径，如果要播放音频更换为本地文件
    myPlayer->play();

}

void Minesweeper::seamusic(){
    myPlayer->setMedia(QUrl::fromLocalFile("D:/Ddocuments/Minesweeper8.1.0/Minesweeper8.1.0/Sound/Jannik - Touch the Rain.mp3"));
    myPlayer->setVolume(80);
    myPlayer->play();
}

void Minesweeper::icemusic(){
    myPlayer->setMedia(QUrl::fromLocalFile("D:/Ddocuments/Minesweeper8.1.0/Minesweeper8.1.0/Sound/Russ - Psycho (Pt. 2).mp3"));
    myPlayer->setVolume(80);
    myPlayer->play();
}

void Minesweeper::acgmusic(){
    myPlayer->setMedia(QUrl::fromLocalFile("D:/Ddocuments/Minesweeper8.1.0/Minesweeper8.1.0/Sound/love.mp3"));
    myPlayer->setVolume(80);
    myPlayer->play();
}

void Minesweeper::startMusic(){
    timer->disconnect();
    timer->stop();
    if (theme==1){
        seamusic();
        connect(timer, SIGNAL(timeout()), this, SLOT(seamusic()));
        timer->start((4*60+26)*1000);
    }
    if (theme==2){
        icemusic();
        connect(timer, SIGNAL(timeout()), this, SLOT(icemusic()));
        timer->start((2*60+42)*1000);
    }
    if (theme==3){
        acgmusic();
        connect(timer, SIGNAL(timeout()), this, SLOT(acgmusic()));
        timer->start((4*60+13)*1000);
    }
}
