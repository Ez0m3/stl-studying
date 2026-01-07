#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

vector<vector<int>> maze = {
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
    {1, 1, 1, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}
};

int n=maze.size();
int m=maze[0].size();

int srow=0,scol=0;
int erow=9,ecol=9;

// int drow[4]={1,0,-1,0};   //右下坐标系的下右上左
// int dcol[4]={0,1,0,-1};

int drow[4]={0,-1,0,1};
int dcol[4]={-1,0,1,0};

vector<vector<bool>> visited(n, vector<bool>(m, false));


bool canGo(int row, int col,const vector<vector<bool>>& visited) {
    return row >= 0 && row < n &&
           col >= 0 && col < m &&
           maze[row][col] == 0 &&
           !visited[row][col];
}

int step=0;

void dfs(int row, int col,int depth){
    ++step;
    if(row==erow&&col==ecol){        //1.终止条件
        std::cout<<"finded!\ndepth:"<<depth<<"\nstep:"<<step<<"\n";
        return;
    }
    for(int i=0;i<=3;++i){
        int nrow=row+drow[i];
        int ncol=col+dcol[i];
        if(canGo(nrow,ncol,visited)){
            visited[nrow][ncol]=true;
            dfs(nrow,ncol,depth+1);
        }
    }
};


int main() {
    visited[0][0]=true;
    dfs(srow,scol,0);
}