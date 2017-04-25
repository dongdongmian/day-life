#include<stdio.h>
#include<memory.h>

bool g[110][310]; //邻接矩阵，true代表有边相连
bool flag,visit[310];    //记录V2中的某个点是否被搜索过
int match[310];   //记录与V2中的点匹配的点的编号
int p,n;   //二分图中左边、右边集合中顶点的数目

bool edmonds(int u)
{
    for (int i = 1; i <= n; ++i)
    {
        if (g[u][i] && !visit[i])   //如果节点i与u相邻并且未被查找过
        {
            visit[i] = true;   //标记i为已查找过
            if (match[i] == -1 || edmonds(match[i]))   //如果i未在前一个匹配M中，或者i在匹配M中，但是从与i相邻的节点出发可以有增广路径
            {
                match[i] = u;  //记录查找成功记录，更新匹配M（即“取反”）
                return true;   //返回查找成功
            }
        }
    }
    return false;
}

int main(void)
{
    int i,j,k,t,v,ans;
    scanf("%d",&t);
    while (t--)
    {
          scanf("%d %d", &p, &n);
          for (i = 1; i <= p; i++)
          {
              for (j = 1; j <= n; j++)
                  g[i][j] = false;
          }
          for (i = 1; i <= n; i++)
              match[i] = -1;
          flag = true;
          for (i = 1; i <= p; i++)
          {
              scanf("%d",&k);
              if (k == 0)
                 flag = false;
              while (k--)
              {
                    scanf("%d",&v);
                    g[i][v]  = true;
              }
          }
          if (flag)
          {
               ans = 0;
               for (i = 1; i <= p; i++)
               {
                   memset(visit,false,sizeof(visit));   //清空上次搜索时的标记
                   if( edmonds(i) )    //从节点i尝试扩展
                       ans++;
               }
               if (ans == p)
                   puts("YES");
               else
                   puts("NO");
          }
          else
              puts("NO");
    }

    return 0;
}
