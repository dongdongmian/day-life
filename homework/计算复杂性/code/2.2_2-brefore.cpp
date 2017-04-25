#include<stdio.h>
#include<memory.h>

bool g[101][101]; //邻接矩阵，true代表有边相连
bool visit[101];    //记录V2中的某个点是否被搜索过
int match[101];   //记录与V2中的点匹配的点的编号
int n,m,k;   //二分图中左边、右边集合中顶点的数目

bool dfs(int u)
{
    for (int i = 1; i <= m; ++i)
    {
        if (g[u][i] && !visit[i])   //如果节点i与u相邻并且未被查找过
        {
            visit[i] = true;   //标记i为已查找过
            if (match[i] == -1 || dfs(match[i]))   //如果i未在前一个匹配M中，或者i在匹配M中，但是从与i相邻的节点出发可以有增广路径
            {
                match[i] = u;  //记录查找成功记录，更新匹配M（即“取反”）
                return true;   //返回查找成功
            }
        }
    }
    return false;
}

inline int MaxMatch()
{
    int i,sum=0;
    memset(match,-1,sizeof(match));
    for(i = 1 ; i <= n ; ++i)
    {
        memset(visit,false,sizeof(visit));   //清空上次搜索时的标记
        if( dfs(i) )    //从节点i尝试扩展
        {
            sum++;
        }
    }
    return sum;
}

int main(void)
{
    int i,j,ans,x,y,num,t=1;
    while (scanf("%d %d %d",&n,&m,&k)!=EOF)
    {
          memset(g,false,sizeof(g));   //初始化
          for (i = 1; i <= k; ++i)
          {
              scanf("%d %d",&x,&y);
              g[x][y] = true;
          }
          ans = MaxMatch();
          num = 0;
          for (i = 1; i <= n; ++i)
          {
              for (j = 1; j <= m; ++j)
              {
                  if(g[i][j] == true)
                  {
                      g[i][j] = false;
                      if(MaxMatch() < ans)
                          num++;
                      g[i][j] = true;
                  }
              }
          }
          printf("Board %d have %d important blanks for %d chessmen.\n",t++,num,ans);
    }
    return 0;
}
