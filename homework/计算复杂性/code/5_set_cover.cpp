#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>
const int N = 50;
int flag[N];
using namespace std;

vector<int> GreedySetCover(int x[],int f[][N],int n,int a,int b)
{
    set<int> U(x,x+n);       // 初始顶点集
    vector<int> C;
    int i,j,k,d;
    int count,num,t;
    set<int>::iterator iter;
    while(!U.empty()){
             // 集合不空时
        count = 0;
        num = 0;
        for(i = 1; i <= a; i++)
            if(!flag[i]){
                t = 0;
                for(j = 1; j <= b; j++)
                    if(U.count(f[i][j]))
                    t++;
                if(t > num){
                    num = t;
                    k = i;
                }
            }

        C.push_back(k);
        flag[k] = 1;
        for(d = 1; d <= b; d++){
            iter = U.find(f[k][d]);
            if(iter != U.end())
            U.erase(iter);
        }
    }
    return C;
}

int main()
{

    int v[N];       // 顶点集合
    int i,j;
    int n;
    scanf("%d",&n);      // 集合大小

    for(i = 0; i < n; i++)
        scanf("%d",&v[i]);

    int f[N][N];
    int x,y;    // x为子集合的个数，y为每个子集合大小
    scanf("%d%d",&x,&y);

    for(i = 1; i <= x; i++)
        for(j = 1; j <= y; j++)
            scanf("%d",&f[i][j]);

    memset(flag,0,sizeof(flag));
    vector<int> result;
    result = GreedySetCover(v,f,n,x,y);
    vector<int>::iterator it = result.begin();

    for(; it != result.end(); it++)
        printf("%d\n",*it);

    return 0;
}
