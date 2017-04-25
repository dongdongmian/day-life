#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int inf=0xfffff;
const int N = 330;
int maxflow, pre[N], dp[N][N];

void Edmonds_Karp(int start, int end, int m){
    while(1){
        queue<int> p;
        int minflow = inf;
        p.push(1);                //源点为1，进队
        memset(pre, 0, sizeof(pre));//初始化增广路径数组，题目中的顶点是从1开始的
        while(!p.empty()){      //bfs找增广路
            int u = p.front();
            p.pop();
            if(u == end)
                break;
            for(int i = 1;i <= m;i++)
                if(dp[u][i] > 0&&pre[i] == 0){ //pre[i]除了记录当前顶点的父亲，还记录当前顶点有没被访问过
                    pre[i] = u;
                    p.push(i);
                }
        }
        if(pre[end] == 0)                   //顶点的父亲为空，表示找不到增广路，很容易理解吧。。
            break;
        for(int i = end;i != start;i = pre[i])  //找出增广路中最小残余量
            minflow = min(minflow, dp[pre[i]][i]);
        for(int i = end;i != start;i = pre[i])  {
            dp[pre[i]][i] -= minflow;           //更新增广路中正反向弧的流量
            dp[i][pre[i]] += minflow;
        }
        maxflow+=minflow;
    }
}

int main(){
    int n, m;
    while(~scanf("%d%d", &n, &m)){
        int i, a, b, f;
        memset(dp, 0, sizeof(dp));
        for(i = 0;i < n;i++){
            scanf("%d%d%d", &a, &b, &f);
            dp[a][b] += f;
        }
        maxflow = 0;
        Edmonds_Karp(1, m, m);
        printf("%d\n", maxflow);
    }
    return 0;
}
