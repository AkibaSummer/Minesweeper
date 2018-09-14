#pragma once
#include <vector>
#include <time.h>

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
	int uncoverNumber;

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
public:
	void init(int, int, int, int);
	void reset();
	int calculate(int, int);//lxm
	MapStatus check();//lxm
	void jCheck(int, int);//检测周围八个方块里是否有雷，有的话不动，将数字其置为非隐藏.传入的位置应当经过判断，是否为符合条件的（显示出来的数字）J
	MapStatus leftClick(int, int);
	MapStatus rightClick(int, int);
	MapStatus doubleClick(int, int);
};
