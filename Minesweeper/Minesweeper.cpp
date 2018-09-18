#include "Minesweeper.h"
#include "ui_Minesweeper.h"
#ifdef _WIN32
#include "Windows.h"
#include <synchapi.h>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();
    //this->setWindowOpacity(0);  //设置窗口透明度
}

void MainWindow::init()
{
    QPainter painter(&maptemp);

    pix.load(":/images/Start.jpg");

    painter.drawPixmap(0,0,1920,1080,pix);
}

void MainWindow::paintEvent(QPaintEvent*w)
{
    Q_UNUSED(w);
    QPainter pen(this);
    pen.drawPixmap(0,0,maptemp);
}

void MainWindow::mousePressEvent(QMouseEvent*m)
{
    int x=m->x();
    int y=m->y();
    if (loc==1){//main
        if(m->button()==Qt::LeftButton){
            if(x>=1243&&x<=1462&&y>=149&&y<=939){       //海洋
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
            }else if(x>=1462&&x<=1696&&y>=149&&y<=860){ //冰川
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
            }else if(x>=1701&&x<=1890&&y>=149&&y<=778){ //动漫
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
            }else if(x>=685&&x<=1181&&y>=67&&y<=267){   //简单
                loadGame(1,8,8,10);
                repaint();
                //closeThis();
            }else if(x>=685&&x<=1181&&y>=270&&y<=470){  //中等
                loadGame(2,18,18,50);
                repaint();
                //closeThis();
            }else if(x>=685&&x<=1181&&y>=473&&y<=673){  //大师
                loadGame(3,28,28,122);
                repaint();
                //closeThis();
            }else if(x>=685&&x<=1181&&y>=676&&y<=876){  //自定义
                customOfGame();
            }else if(x>=685&&x<=1181&&y>=879&&y<=1079){ //游戏规则
                ruleOfGame();
            }else if(x>=1843&&x<=1920&&y>=0&&y<=78){
                closeThis();
            }else{
                update();
            }
        }
    }
    else if(loc==2){//game
        int clickX(-1),clickY(-1);
        int blockSizeX=1000/game.size_x;
        int blockSizeY=1000/game.size_y;
        blockSizeX=blockSizeY=min(blockSizeX,blockSizeY);
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
            if(m->button()==Qt::LeftButton&&m->button()==Qt::RightButton){
                game.doubleClick(clickX,clickY);
                drawGame();
            }
            else if(m->button()==Qt::LeftButton){
                game.leftClick(clickX,clickY);
                drawGame();
            }
            else if(m->button()==Qt::RightButton){
                game.rightClick(clickX,clickY);
                drawGame();
            }
        }
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent*m)
{
    int x=m->x();
    int y=m->y();
    if(loc==2){//game
        int clickX(-1),clickY(-1);
        int blockSizeX=1000/game.size_x;
        int blockSizeY=1000/game.size_y;
        blockSizeX=blockSizeY=min(blockSizeX,blockSizeY);
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
            game.doubleClick(clickX,clickY);
            drawGame();
        }
    }
}
void MainWindow::ruleOfGame()
{
    ru.show();
}

void MainWindow::customOfGame()
{
    cu.show();
    disconnect(&cu,SIGNAL(setCustomInfo(int,int,int,int)),this,SLOT(setCustomGame(int,int,int,int)));
    connect(&cu,SIGNAL(setCustomInfo(int,int,int,int)),this,SLOT(setCustomGame(int,int,int,int)));
}

void MainWindow::changeBackGround(QString picDir)
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


void MainWindow::loadGame(int _diff,int x,int y ,int num){//diff x y num
    ui->label->setVisible(0);
    diff=_diff;
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
    img.img_01=img.img_01.scaled(blockSizeX-4,blockSizeY-4);
    img.img_04=img.img_04.scaled(blockSizeX-4,blockSizeY-4);
    img.img_05=img.img_05.scaled(blockSizeX-4,blockSizeY-4);
    img.img_14=img.img_14.scaled(blockSizeX-4,blockSizeY-4);
    img.img_15=img.img_15.scaled(blockSizeX-4,blockSizeY-4);
    img.img_gameBack=img.img_gameBack.scaled(blockSizeX*game.size_x+20,blockSizeY*game.size_y+20);
    //img.img_menu=img.img_menu.scaled();
    img.img_U=img.img_U.scaled(1920,1080);
    img.img_0201=img.img_0201.scaled(blockSizeX-4,blockSizeY-4);
    img.img_0202=img.img_0202.scaled(blockSizeX-4,blockSizeY-4);
    img.img_0203=img.img_0203.scaled(blockSizeX-4,blockSizeY-4);
    img.img_0204=img.img_0204.scaled(blockSizeX-4,blockSizeY-4);
    img.img_0205=img.img_0205.scaled(blockSizeX-4,blockSizeY-4);
    img.img_0206=img.img_0206.scaled(blockSizeX-4,blockSizeY-4);
    img.img_0207=img.img_0207.scaled(blockSizeX-4,blockSizeY-4);
    img.img_0208=img.img_0208.scaled(blockSizeX-4,blockSizeY-4);
    img.img_03=img.img_03.scaled(blockSizeX-4,blockSizeY-4);
    //img.img_11=img.img_11.scaled(blockSizeX-4,blockSizeY-4);
    drawGame();

}


void MainWindow::drawGame(){
    QPainter painter(&maptemp);
    painter.drawPixmap(0,0,img.img_U);
    int blockSizeX=1000/game.size_x;
    int blockSizeY=1000/game.size_y;
    blockSizeX=blockSizeY=min(blockSizeX,blockSizeY);
    painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2,centerY-(blockSizeY*game.size_y+20)/2,img.img_gameBack);
    for (int i=0;i<game.size_x;i++){
        for (int j=0;j<game.size_y;j++){
            switch (game.getMaps().getMapStatus()[i][j]) {
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

void MainWindow::closeThis()
{
    this->close();
}

void MainWindow::setCustomGame(int diff,int x,int y,int num){
    if (num>=8&&num<=(x-1)*(y-1))
    loadGame(diff ,x,y,num);
}
MainWindow::~MainWindow()
{
    delete ui;
}
