#ifndef RANK_H
#define RANK_H

#include <QMainWindow>
#include <QWidget>
#include "QString"
#include "QFile"
#include "QTextStream"
using namespace std;

struct Player
{
    int difficulty_;
    unsigned int ranking_;
    QString player_;
    double score_;
};
struct Ranking
{
    vector<Player> allRank_;
    Player curRank_;
};

class Rank : public QWidget
{
    Q_OBJECT
public:
    Ranking setInfo(int, QString, double);
    vector<Player> searchData(int);//
    void init();
    Player player;//声明一个叫player结构体
    explicit Rank(QWidget *parent = nullptr);

private:
    int counter;

//signals:

//public slots:
};

#endif // RANK_H
