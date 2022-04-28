#include<bits/stdc++.h>
#define L long long
#define vi vector<int>
#define pb push_back
using namespace std;
int n,m,f[500010][25],h[500010],x[500010],p;
vi a[500010];
inline void dfs(int i)
{
    int j;
    for(j=1;j<=20;j++)
      f[i][j]=f[f[i][j-1]][j-1];
    x[i]=1;
    for(auto j:a[i])
      if(j!=f[i][0])
        {
         f[j][0]=i;
         h[j]=h[i]+1;
         dfs(j);
         x[i]+=x[j];
        }
}
inline int lca(int i,int j)
{
    int k;
    if(h[i]<h[j])
      swap(i,j);
    if(h[i]>h[j])
      {
       for(k=20;k>=0;k--)
         if(h[i]-(1<<k)>h[j])
           i=f[i][k];
       if(f[i][0]==j)
         {
          p=i;
          return j;
         }
       i=f[i][0];
      }
    for(k=20;k>=0;k--)
      if(f[i][k]!=f[j][k])
        i=f[i][k],j=f[j][k];
    return f[i][0];
}
inline void calc(int a,int b)
{
    int k=n+a-b;
    printf("%d.%d\n",k/2,k%2*5);
}
int main()
{
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    int i,j,k;
    scanf("%d%d",&n,&m);
    for(i=1;i<n;i++)
      {
       scanf("%d%d",&j,&k);
       a[j].pb(k);
       a[k].pb(j);
      }
    h[1]=1;
    dfs(1);
    while(m--)
      {
       scanf("%d%d",&i,&j);
       k=lca(i,j);
       calc(h[i]+h[j]-2*h[k]+1,(k==j)?(n-x[p]-1):(x[j]-1));
      }
    return 0;
}

