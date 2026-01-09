#include <iostream>
#include <vector>
#include <stack>

bool isSafe(std::vector<std::vector<int>>& board, int row, int col, int n) {
    for (int i = 0; i < col; i++) {
        if (board[row][i]) return false;
    }
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) return false;
    }
    for (int i = row, j = col; i < n && j >= 0; i++, j--) {
        if (board[i][j]) return false;
    }
    return true;
}

bool solveNQueens(int n) {
    std::vector<std::vector<int>> board(n, std::vector<int>(n, 0));
    std::stack<std::pair<int, int>> stk;
    int col = 0;
    
    while (col >= 0) {
        bool placed = false;
        int row = (col == 0) ? 0 : stk.top().first + 1;
        
        for (; row < n; row++) {
            if (isSafe(board, row, col, n)) {
                if (col < n - 1) {
                    stk.push({row, col});
                    board[row][col] = 1;
                    placed = true;
                    break;
                } else {
                    board[row][col] = 1;
                    return true;
                }
            }
        }
        
        if (placed) {
            col++;
        } else {
            if (stk.empty()) break;
            auto last = stk.top();
            stk.pop();
            board[last.first][last.second] = 0;
            col = last.second;
            row = last.first;
            while (row >= n - 1 && !stk.empty()) {
                last = stk.top();
                stk.pop();
                board[last.first][last.second] = 0;
                col = last.second;
                row = last.first;
            }
            if (row >= n - 1) continue;
            col = last.second;
        }
    }
    return false;
}

int main() {
    int n = 8;
    if (solveNQueens(n)) {
        std::cout << "Solution exists." << std::endl;
    } else {
        std::cout << "No solution." << std::endl;
    }
    return 0;
}
