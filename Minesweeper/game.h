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
    vvi maps;
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
public:
    int size_x,size_y;
	void init(int, int, int, int);
	void reset();
    bool check(int, int);
	MapStatus leftClick(int, int);
	MapStatus rightClick(int, int);
	MapStatus doubleClick(int, int);
	MapStatus getMaps()&;
};
