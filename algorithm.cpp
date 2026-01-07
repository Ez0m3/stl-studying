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
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int n=maze.size();
int m=maze[0].size();

// int srow=0,scol=0;
int erow=n-1,ecol=m-1;

int drow[4]={1,0,-1,0};   //右下坐标系的下右上左
int dcol[4]={0,1,0,-1};

// int drow[4]={0,-1,0,1};    
// int dcol[4]={-1,0,1,0};

vector<vector<bool>> visited(n, vector<bool>(m, false));


bool canGo(int row, int col,const vector<vector<bool>>& visited) {
    return row >= 0 && row < n &&
           col >= 0 && col < m &&
           maze[row][col] == 0 &&
           !visited[row][col];
}

void bfs(int srow,int scol){
    int step{0};
    visited[srow][scol]=true;
    queue<tuple<int,int,int>> q;
    q.push({srow,scol,0});
    while(!q.empty()){
        auto[row,col,depth]=q.front();
        ++step;
        if(row==erow&&col==ecol){
            cout<<"finded!\ndepth:"<<depth<<"\nstep:"<<step;
            return;
        }
        for(int i=0;i<4;++i){
            int nrow=row+drow[i];
            int ncol=col+dcol[i];
            if(canGo(nrow,ncol,visited)){
                visited[nrow][ncol]=1;
                q.push({nrow,ncol,depth+1});
            }
        }
        q.pop();
    }
}

int main() {
    bfs(3,3);
}