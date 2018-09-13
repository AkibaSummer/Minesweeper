#include <bits/stdc++.h>
#include "game.h"
using namespace std;

inline bool MapStatus::getBit(int num,int pos){
    return (num>>(pos-1))&1;
}

MapStatus::MapStatus(int n=0,int m=0){
    map.resize(n);
    for (auto &i:map)
        i.resize(m,0);
};

MapStatus::MapStatus(vvi _map,int _status){
    status=_status;
    
    int n(_map.size()),m(_map.front().size()); // 地图初始化
    map.resize(n);
    for (auto &i:map)
        i.resize(m,0); // 重置为0
        
    mineNumber=0;//取得剩余雷的数量
    for (auto &i:_map)
    for (auto &j:i)
    if (getBit(j,5)&&getBit(j,9)) mineNumber++;
    
    for (int i=0;i<n;i++){ // 地图转换
        for (int j=0;j<m;j++){
            if (_map[i][j]<9) map[i][j]=_map[i][j];
            else if (getBit(_map[i][j],7)) map[i][j]=12;
            else if (getBit(_map[i][j],8)) map[i][j]=13;
            else if (getBit(_map[i][j],9)) map[i][j]=11;
            else if (getBit(_map[i][j],6)) map[i][j]=9;
            else map[i][j]=10;
        }
    }
};

vvi MapStatus::getMapStatus(){ 
    return map;
}

inline bool Game::getBit(int num,int pos){ // 取得数字的某一二进制位
    return (num>>(pos-1))&1;
}

inline void Game::setBit(int &num,int pos,int bit){ // 将某一位设置成指定bit
    if (bit){
        num|=1<<(pos-1);
    }
    else {
        num=~((~num)|(1<<(pos-1)));
    }
}


inline int Game::getNum(int num){
    return num&15;
}

inline bool Game::isMine(int i,int j){ // 判断某一位置是否是雷（加上了边界判断）
    return i<0||i>(int)maps.size()||j<0||j>(int)maps.front().size()?0:
    getBit(maps[i][j],5);
}

void Game::init(int n,int m,int num,int seed=time(0)){
    maps.resize(n); // 初始化地图，分配内存
    for (auto &i:maps)
        i.resize(m,0); // 重置为0
    srand(seed); // 设定随机数种子
    
    for (int i=1;i<=num;i++){ // 放置地雷
        int x=rand()%n; // 随机放置地雷的位置
        int y=rand()%m;
        while (getBit(maps[x][y],5)){
            x=rand()%n;
            y=rand()%m;
        }
        setBit(maps[x][y],5,1);
    }
    
    for (int i=0;i<n;i++){ // 根据地雷的数量决定数字
        for (int j=0;j<m;j++){
            setBit(maps[i][j],9,1); // 将格子设置为隐藏
            if (getBit(maps[i][j],5)) continue;
            int num=0;
            for (int x=i-1;x<=i+1;x++){
                for (int y=j-1;y<=j+1;y++){
                    if (getBit(maps[x][y],5))num++;
                }
            }
            maps[i][j]+=num;
            if (num==0)setBit(maps[i][j],6,1); // 设定空白格子
        }
    }
}

void Game::reset(){
    for (auto &i:maps)
        for (auto &j:i){
            setBit(j,7,0);
            setBit(j,8,0);
            setBit(j,9,1);
        }
}
//lixiaoman------------------------------
int Game::calculate(int x, int y)
	{
		int mineNum = 0;
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
				if(x + i >= 0 && x + i<= xedge && y +j >= 0
					&& y + j<= yedge)//边界限定
				if (isMine(x + i, y + j) == 1)
					mineNum++;                 // 统计以(x,y)为中心的四周的雷数目
		return mineNum;
	}
auto Game:: check() {
		int mine = 0;//被隐藏地雷的数量
		for (i = 0;i <= xedge;i++){
			for (j = 0;j <= yedge;j++){
				if (getBit(maps[i][j], 9)
				{
					mine++;
				}
			}
				
		}
		      if(mine==mineNumber){ return MapStatus(map, 1); }
	}

MapStatus Game::leftClick(int,int){
   
    
	//如果点到地雷，失败
	if (getBit(maps[x][y], 5)) { return MapStatus(map, -1); }
	//如果点到已显示的空白和旗帜，继续游戏
	if (getBit(maps[x][y], 7) || !(getBit(maps[x][y], 9))) { return MapStatus(map, 0); }
	
	//如果点到空白，自动向外扩展(递归)；
    if (getBit(maps[x][y], 9)) {
			if (calculate(x, y) == 0)//如果周围无地雷，继续检测周围是否有数字,空白
			{
				setBit(maps[x][y], 9, 0);
				for (int i = -1; i < 2; i++)
					for (int j = -1; j < 2; j++)
						if (x + i >= 0 && x +i <= xedge && y + j >= 0
							&& y +j<= yedge && !(i == 0 && j == 0)
							&& getBit(maps[x + i]][y + j]], 9))//边界限定，避免递归调用本身，隐藏空白显现
                        {   leftClick(x + i, y + j);}
                             
						else setBit(maps[x][y],9,0);//如果有地雷，显示地雷数目
				return MapStatus(map, 0);//继续游戏
			}
		}
	
	
	 check() ;//判断玩家是否取得游戏胜利
	



	}

//lixiaoman-----------------------------------------------
    
  

MapStatus Game::rightClick(int x,int y){
    if (getBit(maps[x][y],9)){ 
        return MapStatus(maps,0);
    }
    else if (!(getBit(maps[x][y],7)||getBit(maps[x][y],8))){
        setBit(maps[x][y],7,1);
    }
    else if (getBit(maps[x][y],7)){
        setBit(maps[x][y],7,0);
        setBit(maps[x][y],8,1);
    }
    else {
        setBit(maps[x][y],8,0);
    }
    return MapStatus(maps,0);
}

MapStatus Game::doubleClick(int,int){
    return MapStatus();
}

int main(){
    
}
