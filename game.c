#include <bits/stdc++.h>
#include "game.h"
using namespace std;

MapStatus::MapStatus(int n,int m){
    map.resize(n);
    for (auto &i:map)
        i.resize(m,0);
};

inline bool Game::getbit(int num,int pos){
    return (num>>(pos-1))&1;
}



void Game::init(int n,int m,int seed=time(0)){
    
}

void Game::reset(){
    
}

int main(){
    
}