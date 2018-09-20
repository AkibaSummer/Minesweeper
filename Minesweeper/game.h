#pragma once
#include "stdc++.h"

using namespace std;

typedef vector<vector<int>> vvi;

class MapStatus {
    vvi map;
    inline bool getBit(int, int);
public:
    // 1~8表示数字
    // 9表示空白
    // 10表示炸弹
    // 11表示未显示空白
    // 12表示未显示标记旗帜
    // 13表示未显示标记问号
    int status; // 0表示继续进行，1表示胜利，-1表示失败
    int mineNumber;
    int coverNumber;

    MapStatus(int, int);
    MapStatus(vvi, int);
    vvi getMapStatus();
};

class Game {
private:
    // 1~8表示数字
    // 第5位表示是否是地雷
    // 第6位表示是否空白
    // 第7位表示是否标记旗帜
    // 第8位表示是否标记？
    // 第9位表示是否隐藏
    inline bool getBit(int, int);
    inline void setBit(int&, int, int);
    inline int getNum(int);
    inline bool isMine(int, int);
    inline bool isFlag(int, int);
    inline int flagNum(int, int);
    int showBoom();
public:
    vvi maps;
    int size_x,size_y;
    int boomNum;//剩余的雷的数量，可以改变
    int totalNum;//初始的雷的数量，过程中都不改变
    int score;//设置分数
    int tag;//间接的状态表示
    void init(int, int, int, int);
    void reset();
    bool check(int, int);
    void setBack();//用于重绘的一部分
    MapStatus leftClick(int, int);
    MapStatus rightClick(int, int);
    MapStatus doubleClick(int, int);
    MapStatus getMaps()&;
};
