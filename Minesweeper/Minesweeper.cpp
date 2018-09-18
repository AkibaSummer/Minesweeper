#include "Minesweeper.h"
#include "ui_Minesweeper.h"
//#include "Windows.h"
//#include <synchapi.h>

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
                ui->label->setVisible(0);
                loadGame(1,8,8,10);
                repaint();
                //closeThis();
            }else if(x>=685&&x<=1181&&y>=270&&y<=470){  //中等
                ui->label->setVisible(0);
                loadGame(2,18,18,50);
                repaint();
                //closeThis();
            }else if(x>=685&&x<=1181&&y>=473&&y<=673){  //大师
                ui->label->setVisible(0);
                loadGame(3,28,28,122);
                repaint();
                //closeThis();
            }else if(x>=685&&x<=1181&&y>=676&&y<=876){  //自定义
                ui->label->setVisible(0);
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
}

void MainWindow::changeBackGround(QString picDir)
{
    QPainter painter(&maptemp);
    pix.load(picDir);
    for(int i=0;i<50;i++){
        painter.drawPixmap(0,0,1920,1080,pix);
        system("sleep 0.001");
        repaint();
    }
    //pix.load(picDir+".jpg");
    //painter.drawPixmap(0,0,1920,1080,pix);
    //repaint();
}


void MainWindow::loadGame(int _diff,int x,int y ,int num){//diff x y num
    diff=_diff;
    loc=2;
    game.init(x,y,num,time(0));
    drawGame();
}


void MainWindow::drawGame(){
    QPainter painter(&maptemp);
    pix.load(res.img_U);
    painter.drawPixmap(0,0,1920,1080,pix);
    int blockSizeX=1000/game.size_x;
    int blockSizeY=1000/game.size_y;
    blockSizeX=blockSizeY=min(blockSizeX,blockSizeY);
    pix.load(res.img_gameBack);
    pix=pix.scaled(blockSizeX*game.size_x+20,blockSizeY*game.size_y+20);
    painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2,centerY-(blockSizeY*game.size_y+20)/2,pix);
    for (int i=0;i<game.size_x;i++){
        for (int j=0;j<game.size_y;j++){
            switch (game.getMaps().getMapStatus()[i][j]) {
            case 9:
                pix.load(res.img_01);
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);
                break;
            case 10:
                pix.load(res.img_01);
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);

                pix.load(":/images/03.png");
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);
                break;
            case 11:
                pix.load(res.img_15);
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,blockSizeX-4,blockSizeY-4,pix);
                break;
            case 12:
                pix.load(res.img_15);
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);
                pix.load(res.img_04);
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);
                break;
            case 13:
                pix.load(res.img_15);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);
                pix.load(res.img_05);
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);
                break;
            case 1:
                pix.load(res.img_01);
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);

                pix.load(":/images/0201.png");
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);
                break;
            case 2:
                pix.load(res.img_01);
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);

                pix.load(":/images/0202.png");
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);
                break;
            case 3:
                pix.load(res.img_01);
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);

                pix.load(":/images/0203.png");
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);
                break;
            case 4:
                pix.load(res.img_01);
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);

                pix.load(":/images/0204.png");
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);
                break;
            case 5:
                pix.load(res.img_01);
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);

                pix.load(":/images/0205.png");
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);
                break;
            case 6:
                pix.load(res.img_01);
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);

                pix.load(":/images/0206.png");
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);
                break;
            case 7:
                pix.load(res.img_01);
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);

                pix.load(":/images/0207.png");
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);
                break;
            case 8:
                pix.load(res.img_01);
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);

                pix.load(":/images/0208.png");
                pix=pix.scaled(blockSizeX-4,blockSizeY-4);
                painter.drawPixmap(centerX-(blockSizeX*game.size_x+20)/2+i*blockSizeX+12,centerY-(blockSizeY*game.size_y+20)/2+j*blockSizeY+12,pix);
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

MainWindow::~MainWindow()
{
    delete ui;
}
