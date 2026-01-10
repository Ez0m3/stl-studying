#include<vector>
using namespace std;
class Graph{
    vector<vector<int>> g;
    int n;
public:
    Graph(int n):n(n){
        g.resize(n,vector<int>(n,0));
    }
    void add(int u,int v,int w){
        g[u][v]=w;
    }
    void dfs(int u,vector<bool>& vis){
        vis[u]=true;
        for(int v=0;v<n;v++)
            if(g[u][v]&&!vis[v]) dfs(v,vis);
    }
};
