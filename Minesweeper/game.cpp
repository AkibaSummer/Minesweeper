#include "game.h"
using namespace std;

inline bool MapStatus::getBit(int num, int pos) {
	return (num >> (pos - 1)) & 1;
}

MapStatus::MapStatus(int n, int m=0) {
    map.resize(n);
    for (auto &i : map)
        i.resize(m, 0);
};

MapStatus::MapStatus(vvi _map, int _status) {
	status = _status;

	int n(_map.size()), m(_map.front().size()); // 地图初始化
	map.resize(n);
	for (auto &i : map) 
		i.resize(m, 0); 

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

inline bool Game::isFlag(int i, int j) { // 判断某一位置是否是flag（加上了边界判断）
	return i<0 || i >= (int)maps.size() || j<0 || j >= (int)maps.front().size() ? 0 : getBit(maps[i][j], 7);
}

inline int Game::flagNum(int i, int j) {
	int num(0);
			for (int x = i - 1; x <= i + 1; x++) {
				for (int y = j - 1; y <= j + 1; y++) {
					if (isFlag(x, y))num++;
				}
			}
			return num;
}

void Game::init(int n, int m, int num, int seed = time(0)) {
    size_x=n;size_y=m;
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

bool Game::check(int x, int y){
    if (x<0||x>=maps.size()||y<0||y>=maps.front().size()) return 0; //判断位置是否合法
	if (getBit(maps[x][y],5) && !getBit(maps[x][y], 8) && !getBit(maps[x][y], 7)) return 1;//如果是旗子或者标记 
	else if (!getBit(maps[x][y], 9)||getNum(maps[x][y])){//判断点击方块是否为显示或者数字 
	maps[x][y]&= 63; //对前6位保留；旗帜、问号标记与隐藏都改变为0 
	return 0;
}
    maps[x][y]&= 63; //将方块显示并删除所有属性，见上一个注释 
	bool flag(0);
	for (int j = -1; j < 2; j++){
        for (int i = -1; i < 2; i++){
            flag|=check(x + i, y + j);
        }
    }
	return flag;
}

MapStatus Game::leftClick(int x, int y){
	if (getBit(maps[x][y], 5)){
		 return MapStatus(maps, -1); 
	}//如果点到地雷，失败
	else 
		if (!(getBit(maps[x][y], 9))||getBit(maps[x][y],7)||getBit(maps[x][y],8)){//如果点到旗帜和已显示的，继续游戏
			 return MapStatus(maps, 0);
		}
		else 
			{ //如果点到隐藏的空格和数字，先翻开该位置，然后递归掀开周围的方块
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

MapStatus Game::doubleClick(int x, int y) {
    if (getBit(maps[x][y],5))return MapStatus(maps,0);
    bool flag = 0;
	int num = 0;//num代表一共检测到标记与地雷相同的方块个数
    if (!getBit(maps[x][y], 9) && getNum(maps[x][y]) ) {
        if (!(getNum(maps[x][y])==flagNum(x,y)))return MapStatus(maps, 0);
		//该位置是显示的数字且点击有效
			for(int j=-1;j<2;j++){//循环周围的八个格子 
				for(int i=-1;i<2;i++){
                    if(!isFlag(x+i, y+j))//保证不在x，y调用check2
					flag|=check(x+i,y+j);
				} 
			}
			if ((MapStatus(maps, 0).coverNumber == MapStatus(maps, 0).mineNumber))
			//如果当前被隐藏的的数量等于当前的雷数，游戏成功结束
				return MapStatus(maps, flag?-1:1);
			else return MapStatus(maps, -flag);//若还有则继续进行 
	}
}

MapStatus Game::getMaps()& {
	return MapStatus(maps, 0);
};
/*
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
*/
