#ifndef SETNAME_H
#define SETNAME_H

#include <QWidget>
#include "theendwidget.h"

namespace Ui {
class SetName;
}

class SetName : public QWidget
{
    Q_OBJECT

public:
    //void getInfo(int, int, int);
    explicit SetName(QWidget *parent = nullptr);
    ~SetName();
    TheEndWidget endw;
    void paintEvent(QPaintEvent *event);
private slots:
    void enterName();
private:
    Ui::SetName *ui;
};

#endif // SETNAME_H
