#include "minesweeper.h"
#include <QApplication>
#include <QIcon>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Minesweeper w;
    w.showFullScreen();
    w.setWindowIcon(QIcon(":img/photo.png"));
    w.setWindowTitle("扫雷");
    return a.exec();
}
