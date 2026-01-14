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
//vector<vector<bool>> visited(n, vector<bool>(m, false));

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

void Backtracking_dfs(int srow,int scol){
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int count=0;  //记录步数比较性能
    int result_num=0;
    vector<pair<int,int>>path;
    auto backtrack=[&](auto fuc_self,int row,int col)->void{
        ++count;
        if(row<0||row>=n||col<0||col>=m||visited[row][col]||maze[row][col])return;
        visited[row][col]=true;
        path.push_back({row,col});

        if(row==erow&&col==ecol){         //1.finded
            cout<<"找到路径"<<result_num<<":";
            for(auto [row,col]:path){
                cout<<"-->("<<row<<","<<col<<")";
            }
            cout<<"\n";
            ++result_num;
            cout<<"\n\n";
        }else{
            for(int i=0;i<4;++i){             //2.notfind
                int nrow=row+drow[i];
                int ncol=col+dcol[i];
                if(canGo(nrow,ncol,visited)){
                    fuc_self(fuc_self,nrow,ncol);
                }
            }
        }   
            visited[row][col]=false;         //back
            path.pop_back();
        };
        backtrack(backtrack,srow,scol);
        cout<<"\n"<<count<<"\n"<<result_num;
    }
int main(){
    Backtracking_dfs(2,3);
}