#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> vvi;

class MapStatus{
public:
    vvi map;
    // 1~8表示数字
    // 9表示空白
    // 10表示炸弹
    // 11表示未显示空白
    // 12表示未显示标记旗帜
    // 13表示未显示标记问号
    bool status;
    int mineNumber;
    MapStatus(int,int);
};

class Game{
private:
    vvi maps;  
    // 负数表示隐藏，正数表示显示
    // 1~8表示数字
    // 第5位表示是否是地雷
    // 第6位表示是否空白
    // 第7位表示是否标记旗帜
    // 第8位表示是否标记？
    inline bool getbit(int,int);
public:
    void init(int,int,int);
    void reset();
    MapStatus leftClick(int,int);
    MapStatus rightClick(int,int);
    MapStatus doubleClick(int,int);
};