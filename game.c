#include <bits/stdc++.h>
#include "game.h"
using namespace std;

inline bool MapStatus::getBit(int num, int pos) {
	return (num >> (pos - 1)) & 1;
}

MapStatus::MapStatus(int n = 0, int m = 0) {
	map.resize(n);
	for (auto &i : map)
		i.resize(m, 0);
};

MapStatus::MapStatus(vvi _map, int _status) {
	status = _status;

	int n(_map.size()), m(_map.front().size()); // 地图初始化//这也行？！ 
	map.resize(n);
	for (auto &i : map)//？？？？？？？ 
		i.resize(m, 0); // 重置为0

	mineNumber = 0;//取得剩余雷的数量
	coverNumber = 0;//取得剩余隐藏数量
	for (auto &i : _map)
		for (auto &j : i) {
			if (getBit(j, 5) && getBit(j, 9)) mineNumber++;
			if (getBit(j, 9)) coverNumber++;
		}

	for (int i = 0; i<n; i++) { // 地图转换
		for (int j = 0; j<m; j++) {
			if (_map[i][j]<9) map[i][j] = _map[i][j];
			else if (getBit(_map[i][j], 7)) map[i][j] = 12;
			else if (getBit(_map[i][j], 8)) map[i][j] = 13;
			else if (getBit(_map[i][j], 9)) map[i][j] = 11;
			else if (getBit(_map[i][j], 6)) map[i][j] = 9;
			else map[i][j] = 10;
		}
	}
};

vvi MapStatus::getMapStatus() {
	return map;
}

inline bool Game::getBit(int num, int pos) { // 取得数字的某一二进制位
	return (num >> (pos - 1)) & 1;
}

inline void Game::setBit(int &num, int pos, int bit) { // 将某一位设置成指定bit
	if (bit) {
		num |= 1 << (pos - 1);
	}
	else {
		num = ~((~num) | (1 << (pos - 1)));
	}
}


inline int Game::getNum(int num) {
	return num & 15;
}

inline bool Game::isMine(int i, int j) { // 判断某一位置是否是雷（加上了边界判断）
	return i<0 || i >= (int)maps.size() || j<0 || j >= (int)maps.front().size() ? 0 : getBit(maps[i][j], 5);
}

void Game::init(int n, int m, int num, int seed = time(0)) {
	maps.resize(n); // 初始化地图，分配内存
	for (auto &i : maps)
		i.resize(m, 0); // 重置为0
	srand(seed); // 设定随机数种子

	for (int i = 1; i <= num; i++) { // 放置地雷
		int x = rand() % n; // 随机放置地雷的位置
		int y = rand() % m;
		while (getBit(maps[x][y], 5)) {
			x = rand() % n;
			y = rand() % m;
		}
		setBit(maps[x][y], 5, 1);
	}

	for (int i = 0; i<n; i++) { // 根据地雷的数量决定数字
		for (int j = 0; j<m; j++) {
			setBit(maps[i][j], 9, 1); // 将格子设置为隐藏
			if (getBit(maps[i][j], 5)) continue;
			int num = 0;
			for (int x = i - 1; x <= i + 1; x++) {
				for (int y = j - 1; y <= j + 1; y++) {
					if (isMine(x, y))num++;
				}
			}
			maps[i][j] += num;
			if (num == 0)setBit(maps[i][j], 6, 1); // 设定空白格子
		}
	}
}

void Game::reset() {
	for (auto &i : maps)
		for (auto &j : i) {
			setBit(j, 7, 0);
			setBit(j, 8, 0);
			setBit(j, 9, 1);
		}
}


void Game::check(int x, int y) {//检测周围八个方块里是否有雷，有的话不动，将数字其置为非隐藏
    //传入的位置应当经过判断，是否为符合条件的（显示出来的数字），插旗子的地方一定是不隐藏的
    if (!getBit(maps[x][y], 9))return;
    setBit(maps[x][y], 9, 0); //先置为非隐藏
    for (int j = -1; j < 2; j++) {
        for (int i = -1; i < 2; i++) {
            if ((0 <= x + i) && (x + i <= (int)maps.size() - 1) && (0 <= y + j) && (y + j <= (int)maps.front().size() - 1) && (i || j)) {
                //递归过程中的边界限定,且不能同时为0
                if (!(1<=getNum(maps[x][y])&&getNum(maps[x][y])<=8)) {//若未检测到雷，进行递归
                    check(x + i, y + j);
                }
                else return;//检测到雷，停止递归，返回上一层调用继续进行循环
                //所有情况都会跳到这句
            }
        }
    }
}


MapStatus Game::leftClick(int x, int y){
	if (getBit(maps[x][y], 5)){
		 return MapStatus(maps, -1); 
	}//如果点到地雷，失败
	else 
		if (getBit(maps[x][y], 7) || !(getBit(maps[x][y], 9))){//如果点到旗帜和已显示的，继续游戏
			 return MapStatus(maps, 0); 
		}
		else 
			{ //如果点到隐藏的空格和数字，先翻开该位置，然后递归掀开周围的方块
				setBit(maps[x][y],9,0); 
                check(x , y);
                if ((MapStatus(maps, 0).coverNumber == MapStatus(maps, 0).mineNumber))
				//如果当前被隐藏的的数量等于当前的雷数游戏结束 
				return MapStatus(maps, 1);
				else return MapStatus(maps, 0);
            }
}
		


MapStatus Game::rightClick(int x, int y) {
	if (!getBit(maps[x][y], 9)) {
		return MapStatus(maps, 0);
	}
	else if (!(getBit(maps[x][y], 7) || getBit(maps[x][y], 8))) {
		setBit(maps[x][y], 7, 1);
	}
	else if (getBit(maps[x][y], 7)) {
		setBit(maps[x][y], 7, 0);
		setBit(maps[x][y], 8, 1);
	}
	else {
		setBit(maps[x][y], 8, 0);
	}
	return MapStatus(maps, 0);
}

//蒋雪莲
MapStatus Game::doubleClick(int x, int y) {
	int num = 0;//num代表一共检测到标记与地雷相同的方块个数
	for(int j = -1;j < 2; j++){
		for(int i = -1;i < 2;i++){
			if(getBit(maps[x][y],7)&&getBit(maps[x][y],5))//如果雷跟旗子标记正确num加一 
				num++;
		}		
		
	}
	if ((0 <= x) && (x <= (int)maps.size() - 1) && (0 <= y) && (y <= (int)maps.front().size() - 1)
		&& !getBit(maps[x][y], 9) && (1 <= getNum(maps[x][y])) && (getNum(maps[x][y]) <= 8)) {//该是显示的数字且点击有效
		if (num == getNum(maps[x][y])) {//如果旗子判断正确就开始递归，并且判断是否游戏成功
			check(x, y);//掀开周围的空格以及数字 
			if ((MapStatus(maps, 0).coverNumber == MapStatus(maps, 0).mineNumber))
			//如果当前被隐藏的的数量等于当前的雷数，游戏成功结束
				return MapStatus(maps, 1);
			else return MapStatus(maps, 0);//若还有则继续进行
		}
		else return MapStatus(maps, -1);//没标对就炸，因为这个被点击的地方一定是显示的数字 
		}
	else return MapStatus(maps,0);//如果点击无效，返回0 
}




MapStatus Game::getMaps()& {
	return MapStatus(maps, 0);
};

int main() {
	int x, y, num;
	cout << "please input size(x y)" << endl;
	cin >> x >> y;
	cout << "Please input boomsize" << endl;
	cin >> num;
	Game game;
	game.init(x, y, num);
	do {
		for (auto &i : game.getMaps().getMapStatus()) {
			for (auto &j : i) {
				if (j<9)cout << j;
				else if (j == 9)cout << ' ';
				else if (j == 10)cout << 'b';
				else if (j == 11)cout << '_';
				else if (j == 12)cout << 'q';
				else if (j == 13)cout << '?';
			}
			cout << endl;
		}
		char c;
		cin >> c >> x >> y;
		if (c == 'l')game.leftClick(x, y);
		else if (c == 'r')game.rightClick(x, y);
		else if (c == 'd')game.doubleClick(x, y);
	} while (true);
}
