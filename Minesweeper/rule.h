#ifndef RULE_H
#define RULE_H

#include <QWidget>
#include "QPainter"
#include "QMouseEvent"

namespace Ui {
class Rule;
}

class Rule : public QWidget
{
    Q_OBJECT

public:
    QPixmap maptemp=QPixmap(696,647);

    void showRule();
    void paintEvent(QPaintEvent*);

    explicit Rule(QWidget *parent = nullptr);
    ~Rule();

private slots:
    void closeThis();

private:
    Ui::Rule *ui;
};

#endif // RULE_H
