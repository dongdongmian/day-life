#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int const N= 20010, M= 880010;
int n, m, idx= -1, S, T;

#define min(a,b) ( (a)< (b)? (a): (b) )

struct Edge{
    int wt, v;

    Edge* next;
 }tb[M];

Edge* mat[N];
int h[N], que[N];

void inline add( int u, int v, int x, int y ){
    idx++;
    tb[idx].wt= x; tb[idx].v= v;
    tb[idx].next= mat[u]; mat[u]= tb+ idx;
    idx++;
    tb[idx].wt= y; tb[idx].v= u;
    tb[idx].next= mat[v]; mat[v]= tb+ idx;
 }

inline Edge* reserve( Edge* p ){
    return tb+ ((p-tb)^1);
 }

int bfs(){
    int head= 0, tail= 0;
    for( int i= 0; i<= T; ++i )
        h[i]= -1;

    que[0]= S; h[S]= 0;
    while( head<= tail ){
        int u= que[head++];
        for( Edge* p= mat[u]; p; p= p->next ){
            int v= p->v, w= p->wt;
            if( h[v]== -1 && w> 0 ){
                h[v]= h[u]+ 1; que[++tail]= v;
            }
        }
    }
    return h[T]!= -1;
 }

int dfs( int u, int flow ){
    if( u== T )
        return flow;

    int tf= 0, f;
    for( Edge* p= mat[u]; p; p= p->next ){
        int v= p->v, w= p->wt;

        if( h[v]== h[u]+ 1 && w> 0 && tf< flow && ( f= dfs( v, min( w, flow- tf ) ) ) ){
            p->wt-= f;
            reserve(p)->wt+= f;
            tf+= f;
        }
    }
    if( tf== 0 ) h[u]= -1;

    return tf;
 }

int inline read(){
    char ch;
    int d;

    while( ch= getchar(), ch== ' ' || ch== 'n');
        d= ch- '0';

    while( ch= getchar(), ch>= '0' && ch<= '9' )
        d= d* 10+ ch- '0';

    return d;
 }

int main(){

    scanf("%d%d",&n,&m );
    S= 0, T= n+ 1; idx= -1;

    for( int i= 0; i<= n+ 1; ++i )
        mat[i]= 0;

    for( int i= 1; i<= n; ++i ){
        int x, y;
        x= read(),y=read();
        add( S, i, x, 0 ); add( i, T, y, 0 );
    }

    for( int i= 0; i< m; ++i ){
        int x, y, z;
        x=read(),y=read(),z=read();
        add( x, y, z, z );
    }

    int ans= 0;
    while( bfs()) ans+= dfs( S, 0x7fffffff );
    printf("%dn", ans );
    return 0;
 }
