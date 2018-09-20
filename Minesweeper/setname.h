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
private slots:
    void enterName();
private:
    Ui::SetName *ui;
    TheEndWidget endw;
};

#endif // SETNAME_H
