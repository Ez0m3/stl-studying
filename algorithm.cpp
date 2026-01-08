#include <iostream>
#include <vector>
#include <queue>
#include <stack>
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

// int drow[4]={1,0,-1,0};   //右下坐标系的下右上左
// int dcol[4]={0,1,0,-1};
int drow[4]={0,-1,0,1};    
int dcol[4]={-1,0,1,0};

bool canGo(int row, int col,const vector<vector<bool>>& visited) {
    return row >= 0 && row < n &&
           col >= 0 && col < m &&
           maze[row][col] == 0 &&
           !visited[row][col];
}

void bfs(int srow,int scol){
    vector<vector<bool>> visited(n, vector<bool>(m, false));
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

void dfs(int srow,int scol){
    vector<vector<bool>> visited(n, vector<bool>(m, false));  //-1.初始化
    visited[srow][scol]=true;
    stack<tuple<int,int,int>> s;
    int step=0;
    s.push({srow,scol,0});

    while(!s.empty()){                //0.进入查找
        auto [row,col,depth]=s.top();
        s.pop();
        ++step;

        if(row==erow&&col==ecol){          //1.找到后中止
            std::cout<<"finded!\ndepth:"<<depth<<"\nstep:"<<step;
            return;          
        }

        for(int i=3;i>=0;--i){              //2.增加邻居
            int nrow=row+drow[i];
            int ncol=col+dcol[i];
            if(canGo(nrow,ncol,visited)){
                visited[nrow][ncol]=true;
                s.push({nrow,ncol,depth+1});
            }
        }
    }
}

void backtrack(int row, int col, int depth, vector<vector<bool>>& visited, vector<pair<int, int>>& path) {
    // 1. 终止条件：到达终点
    if (row == erow && col == ecol) {
        cout << "找到一条路径！长度: " << depth << endl;
        // 如果想看具体路径，可以遍历 path
        return;
    }

    // 2. 遍历所有选择（上下左右）
    for (int i = 0; i < 4; ++i) {
        int nrow = row + drow[i];
        int ncol = col + dcol[i];

        // 3. 约束检查
        if (canGo(nrow, ncol, visited)) {
            // --- 做选择 ---
            visited[nrow][ncol] = true;
            path.push_back({nrow, ncol});

            // --- 进入递归 ---
            backtrack(nrow, ncol, depth + 1, visited, path);

            // --- 撤销选择 (这就是回溯的核心！) ---
            path.pop_back();
            visited[nrow][ncol] = false; 
        }
    }
}

int main(){
    dfs(3,3);
}