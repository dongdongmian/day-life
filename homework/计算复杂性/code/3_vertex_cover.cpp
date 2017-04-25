#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#define CLR(x) memset(x,0,sizeof(x))
#define __CLR(x) memset(x,-1,sizeof(x))
using namespace std;

struct edge
{
    int to,next;
}e[1505];
int h[1505],dp[1505][2],num=1;
void addedge(int u,int v)
{
    e[num].to=v;
    e[num].next=h[u];
    h[u]=num++;
}
void dfs(int u)
{
    int v,i;
    dp[u][0]=0;
    dp[u][1]=1;
    for(i=h[u];i!=-1;i=e[i].next)
    {
        v=e[i].to;
        dfs(v);
        dp[u][0]+=dp[v][1];
        dp[u][1]+=min(dp[v][0],dp[v][1]);
    }
}
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        __CLR(h);
        int rt=-1;
        num=1;
        for(int i=1; i<=n; i++)
        {
            int u,k;
            scanf("%d:(%d)",&u,&k);
            for(int j=1; j<=k; j++)
            {
                int v;
                scanf("%d",&v);
                addedge(u,v);
            }
            if(rt==-1) rt=u;
        }
        dfs(rt);
        int res=min(dp[rt][0],dp[rt][1]);
        printf("%d\n",res);
    }
}

