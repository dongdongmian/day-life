#include <stdio.h>
#include <cstdlib>
#include <memory.h>
const int Max =0x7fffffff;
const int N=50;

int n;
int g[N][N],dis[N],visited[N];

int prim()
{
  int i,j;
  int pos,min;
  int ans=0;
  memset(visited,0,sizeof(visited));
  visited[1]=1;pos=1;
  //assign a value to the dis[N] first
  for(i=2;i<=n;i++)
    dis[i]=g[pos][i];
  for(i=1;i<n;i++)
  {
    min=Max;
    for(j=1;j<=n;j++)
    {
      if(visited[j]==0&&min>dis[j])
      {
        min=dis[j];
        pos=j;
      }
    }
    printf("The node being traversed is :%d\n",pos);
    ans+=min;
    printf("The value of ans is %d\n",ans);
    //mark the node
    visited[pos]=1;
    //update the weight
    for(j=1;j<=n;j++)
      if(visited[j]==0&&dis[j]>g[pos][j])
        dis[j]=g[pos][j];
  }
  return ans;
}

int main()
{
  int i=1,j=1;
  int ans=0;
  int w;
  printf("Please enter the number of the nodes:\n");
  scanf("%d",&n);
  for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
    {
      if(i==j)
        g[i][j]=0;
      else
        g[i][j]=Max;
    }
  printf("Please enter the number of the edges:\n");
  int edgenum;
  scanf("%d",&edgenum);
  int v1,v2;
  printf("Please enter the number and the corresponding weight:\n");
  for(i=1;i<=edgenum;i++)
  {
    scanf("%d%d%d",&v1,&v2,&w);
    g[v1][v2]=g[v2][v1]=w;
  }
  ans=prim();
  printf("The sum of the weight of the edges is:%d\n",ans);
  system("pause");
  return 0;

}
