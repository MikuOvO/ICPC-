#include<cstdio>
#define N 100010
typedef long long ll;
inline void read(int&a){char c;while(!(((c=getchar())>='0')&&(c<='9')));a=c-'0';while(((c=getchar())>='0')&&(c<='9'))(a*=10)+=c-'0';}
int n,m,K,i,x,y,g[N],nxt[N<<1],v[N<<1],ok[N<<1],ed=1,son[N],f[N],size,now,fa[N],exa,exb,to[N],way[N],cnt,in[N],dis[N],t[N],pos;
ll ans,bit[N];
inline void addedge(int x,int y){v[++ed]=y,nxt[ed]=g[x],ok[ed]=1,g[x]=ed;}
int F(int x){return fa[x]==x?x:fa[x]=F(fa[x]);}
inline void add(int x){for(;x<=n;x+=x&-x)if(t[x]!=pos)t[x]=pos,bit[x]=1;else bit[x]++;}
inline void del(int x){for(;x<=n;x+=x&-x)bit[x]--;}
inline ll sum(int x){if(x<0)return 0;ll y=0;for(;x;x-=x&-x)if(t[x]==pos)y+=bit[x];return y;}
void findroot(int x,int pre){
  son[x]=1;f[x]=0;
  for(int i=g[x];i;i=nxt[i])if(ok[i]&&v[i]!=pre){
    findroot(v[i],x);
    son[x]+=son[v[i]];
    if(son[v[i]]>f[x])f[x]=son[v[i]];
  }
  if(size-son[x]>f[x])f[x]=size-son[x];
  if(f[x]<f[now])now=x;
}
void dfscal(int x,int pre,int dep){
  ans+=sum(n)-sum(K-dep-1);
  for(int i=g[x];i;i=nxt[i])if(ok[i]&&v[i]!=pre)dfscal(v[i],x,dep+1);
}
void dfsadd(int x,int pre,int dep){
  add(dep+1);
  for(int i=g[x];i;i=nxt[i])if(ok[i]&&v[i]!=pre)dfsadd(v[i],x,dep+1);
}
void solve(int x){
  int i;
  pos++,add(1);
  for(i=g[x];i;i=nxt[i])if(ok[i])dfscal(v[i],x,1),dfsadd(v[i],x,1);
  for(i=g[x];i;i=nxt[i])if(ok[i])ok[i^1]=0,f[0]=size=son[v[i]],findroot(v[i],now=0),solve(now);
}
void path(int x,int pre,int d){
  to[x]=pre,add(dis[x]=d);
  for(int i=g[x];i;i=nxt[i])if(v[i]!=pre)path(v[i],x,d+1);
}
void treecal(int x,int pre,int d){
  ans+=sum(n)-sum(K-d-1);
  for(int i=g[x];i;i=nxt[i])if(v[i]!=pre&&!in[v[i]])treecal(v[i],x,d+1);
}
void treedel(int x,int pre){
  del(dis[x]);
  for(int i=g[x];i;i=nxt[i])if(v[i]!=pre&&!in[v[i]])treedel(v[i],x);
}
int main(){
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
  read(n),read(m),read(K);
  for(i=1;i<=n;i++)fa[i]=i;
  while(m--){
    read(x),read(y);
    if(F(x)==F(y))exa=x,exb=y;else fa[fa[x]]=fa[y],addedge(x,y),addedge(y,x);
  }
  f[0]=size=n,findroot(1,now=0),solve(now);
  if(exa){
    pos++,path(exa,0,1);
    for(i=exb;i;i=to[i])in[way[++cnt]=i]=1;
    for(i=1;i<cnt;i++)treedel(way[i],0),treecal(way[i],0,i);
  }
  return printf("%lld",ans),0;
}
