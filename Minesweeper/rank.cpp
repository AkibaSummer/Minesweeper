#include "rank.h"
extern vector<Player> easPlLi;	//简单成绩列表
extern vector<Player> midPlLi;	//中等成绩列表
extern vector<Player> difPlLi;	//困难成绩列表
extern vector<Player> cosPlLi;	//自定成绩列表


//分数降序
int cmp(Player &player1, Player &player2) {//比较两个玩家分数高低
    return player1.score_ > player2.score_;//如果第一个高，返回1
}

Rank::Rank(QWidget *parent) : QWidget(parent)
{
    player = {
        1,
        1,
        "LiHua",
        100
    };
}

Ranking Rank::setInfo(int difficulty, QString playerName, double score) {
    player = {
        difficulty,
        1,
        playerName,
        score
    };

    if (1==difficulty) {
        easPlLi.push_back({ difficulty,1,playerName,score });

        //排序
        sort(easPlLi.begin(), easPlLi.end(), cmp);

        //写入文件
        QFile file("EasyPlayer.txt");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        for (unsigned int i=0;i<easPlLi.size();i++) {
            easPlLi[i].ranking_ = i + 1;
            out << easPlLi[i].ranking_<<' '
                << easPlLi[i].player_<<' '
                << easPlLi[i].score_<<'\n';
        }
        file.close();

        Player curPlayer = easPlLi[0];
        for (unsigned int i = 1; easPlLi[i-1].player_ != playerName; i++) {
            curPlayer = easPlLi[i];
        }
        Ranking easRank = {
            easPlLi,
            curPlayer
        };
        return easRank;
    }
    else if (2==difficulty) {
        midPlLi.push_back({ difficulty,1,playerName,score });

        //排序
        sort(midPlLi.begin(), midPlLi.end(), cmp);

        //写入文件
        QFile file("MiddlePlayer.txt");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        for (unsigned int i=0;i<midPlLi.size();i++) {
            midPlLi[i].ranking_ = i + 1;
            out << midPlLi[i].ranking_<<' '
                << midPlLi[i].player_<<' '
                << midPlLi[i].score_<<'\n';
        }
        file.close();

        Player curPlayer = midPlLi[0];
        for (unsigned int i = 1; midPlLi[i-1].player_ != playerName; i++) {
            curPlayer = midPlLi[i];
        }
        Ranking midRank = {
            midPlLi,
            curPlayer
        };
        return midRank;
    }
    else if (3==difficulty) {
        difPlLi.push_back({ difficulty,1,playerName,score });

        //排序
        sort(difPlLi.begin(), difPlLi.end(), cmp);

        //写入文件
        QFile file("DifficultPlayer.txt");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        for (unsigned int i=0;i<difPlLi.size();i++) {
            difPlLi[i].ranking_ = i + 1;
            out << difPlLi[i].ranking_<<' '
                << difPlLi[i].player_<<' '
                << difPlLi[i].score_<<'\n';

        }
        file.close();

        Player curPlayer = difPlLi[0];
        for (unsigned int i = 1; difPlLi[i-1].player_ != playerName; i++) {
            curPlayer = difPlLi[i];
        }
        Ranking difRank = {
            difPlLi,
            curPlayer
        };
        return difRank;
    }else if (4==difficulty) {
        cosPlLi.push_back({ difficulty,1,playerName,score });

        //排序
        sort(cosPlLi.begin(), cosPlLi.end(), cmp);

        //写入文件
        QFile file("CustomPlayer.txt");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        for (unsigned int i=0;i<cosPlLi.size();i++) {
            cosPlLi[i].ranking_ = i + 1;
            out << cosPlLi[i].ranking_<<' '
                << cosPlLi[i].player_<<' '
                << cosPlLi[i].score_<<'\n';

        }
        file.close();

        Player curPlayer = cosPlLi[0];
        for (unsigned int i = 1; cosPlLi[i-1].player_ != playerName; i++) {
            curPlayer = cosPlLi[i];
        }
        Ranking comRank = {
            cosPlLi,
            curPlayer
        };
        return comRank;
    }
    else {
        Ranking noRank;
        return noRank;
    }
}

vector<Player> Rank::searchData(int difficulty) {
    if (1 == difficulty) {
        return easPlLi;
    }
    else if (2 == difficulty) {
        return midPlLi;
    }
    else {
        return difPlLi;
    }
}

void Rank::init() {
    for(int i=0;i<1;i++){
        easPlLi.clear();
        QFile file("EasyPlayer.txt");
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
            return;
        }
        Player getIn;
        QTextStream in(&file);

        for (;!in.atEnd();) {
            in >> getIn.ranking_ >> getIn.player_ >> getIn.score_;
            easPlLi.push_back(getIn);
        }
        file.close();
    }


    for(int i=0;i<1;i++){
        midPlLi.clear();
        QFile file("MiddlePlayer.txt");
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
            return;
        }
        Player getIn;
        QTextStream in(&file);

        for (;!in.atEnd();) {
            in >> getIn.ranking_ >> getIn.player_ >> getIn.score_;
            midPlLi.push_back(getIn);
        }
        file.close();
    }

    for(int i=0;i<1;i++){
        difPlLi.clear();
        QFile file("DifficultPlayer.txt");
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
            return;
        }
        Player getIn;
        QTextStream in(&file);

        for (;!in.atEnd();) {
            in >> getIn.ranking_ >> getIn.player_ >> getIn.score_;
            difPlLi.push_back(getIn);
        }
        file.close();
    }

    for(int i=0;i<1;i++){
        cosPlLi.clear();
        QFile file("customPlayer.txt");
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
            return;
        }
        Player getIn;
        QTextStream in(&file);

        for (;!in.atEnd();) {
            in >> getIn.ranking_ >> getIn.player_ >> getIn.score_;
           cosPlLi.push_back(getIn);
        }
        file.close();
    }

}
