#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstring>

using namespace std;

// ==================== 迷宫定义和工具函数 ====================
class Maze {
private:
    vector<vector<int>> grid;      // 迷宫网格 0=可走, 1=墙
    vector<vector<bool>> visited;  // 访问标记
    int rows, cols;
    pair<int, int> start, end;     // 起点和终点
    
    // 方向数组: 上、右、下、左
    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, 1, 0, -1};
    
public:
    // 构造函数：自动生成迷宫
    Maze(int r = 10, int c = 10) : rows(r), cols(c) {
        grid.resize(rows, vector<int>(cols, 0));
        visited.resize(rows, vector<bool>(cols, false));
        
        // 生成随机迷宫（简化版：四周是墙，中间有些障碍）
        generateMaze();
        
        // 设置起点和终点
        start = {1, 1};
        end = {rows-2, cols-2};
        grid[start.first][start.second] = 0;
        grid[end.first][end.second] = 0;
    }
    
    void generateMaze() {
        // 简单迷宫：四周是墙，中间有随机障碍
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                if(i == 0 || i == rows-1 || j == 0 || j == cols-1) {
                    grid[i][j] = 1;  // 边界是墙
                } else if(rand() % 4 == 0) {  // 25%概率生成墙
                    grid[i][j] = 1;
                } else {
                    grid[i][j] = 0;
                }
            }
        }
        // 确保起点和终点是通路
        grid[0][0] = 0;
        grid[rows-1][cols-1] = 0;
    }
    
    // 打印迷宫
    void printMaze() {
        cout << "\n迷宫地图 (" << rows << "x" << cols << "):\n";
        cout << "S:起点, E:终点, #:墙, .:路\n";
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                if(i == start.first && j == start.second) cout << "S ";
                else if(i == end.first && j == end.second) cout << "E ";
                else if(grid[i][j] == 1) cout << "# ";
                else cout << ". ";
            }
            cout << endl;
        }
    }
    
    // 打印路径
    void printPath(const vector<pair<int, int>>& path) {
        vector<vector<char>> display(rows, vector<char>(cols, '.'));
        
        // 标记墙
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                if(grid[i][j] == 1) display[i][j] = '#';
            }
        }
        
        // 标记路径
        for(const auto& p : path) {
            display[p.first][p.second] = '*';
        }
        
        // 标记起点终点
        display[start.first][start.second] = 'S';
        display[end.first][end.second] = 'E';
        
        cout << "\n路径可视化 (*表示路径):\n";
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                cout << display[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    // 判断位置是否有效
    bool isValid(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0;
    }
    
    // 重置访问标记
    void resetVisited() {
        for(auto& row : visited) {
            fill(row.begin(), row.end(), false);
        }
    }
    
    // ==================== 这是你需要实现的部分 ====================
    // 深度优先搜索 (DFS) - 返回路径
    vector<pair<int, int>> dfs() {
    vector<pair<int, int>> path;
    
    // 使用栈进行DFS
    stack<pair<int, int>> stk;
    
    // 用于记录路径（记录每个节点的父节点）
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));
    
    // 重置访问标记
    resetVisited();
    
    // 1. 将起点入栈并标记已访问
    stk.push(start);
    visited[start.first][start.second] = true;
    
    cout << "DFS开始搜索...\n";
    int steps = 0;
    
    while (!stk.empty()) {
        steps++;
        
        // 2. 弹出栈顶元素
        auto [x, y] = stk.top();
        stk.pop();
        
        // 调试信息：可以取消注释查看搜索过程
        // cout << "步骤" << steps << ": 访问 (" << x << ", " << y << ")\n";
        
        // 3. 如果到达终点，回溯构建路径
        if (x == end.first && y == end.second) {
            cout << "DFS找到终点！总步数：" << steps << "\n";
            
            // 回溯构建路径
            while (x != -1 && y != -1) {
                path.push_back({x, y});
                auto [px, py] = parent[x][y];
                x = px;
                y = py;
            }
            
            // 反转路径（从起点到终点）
            reverse(path.begin(), path.end());
            return path;
        }
        
        // 4. 向四个方向探索
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            // 检查新位置是否有效且未访问
            if (isValid(nx, ny) && !visited[nx][ny]) {
                // 标记已访问并记录父节点
                visited[nx][ny] = true;
                parent[nx][ny] = {x, y};
                
                // 将新位置入栈
                stk.push({nx, ny});
            }
        }
    }
    
    // 如果栈空了还没找到终点
    cout << "DFS未找到路径！总步数：" << steps << "\n";
    return path;  // 返回空路径
}
};
    int main(){
        Maze m1;
        m1.generateMaze();
        m1.printMaze();
        m1.printPath(m1.dfs());
    }