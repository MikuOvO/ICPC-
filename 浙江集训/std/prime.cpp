#include<bits/stdc++.h>
#define L long long
#define U unsigned long long
using namespace std;
int m,x[100000],q,t=168;
L n,s,a;
U p;
bool w[200000000];
unordered_map<L,L> h;
inline L dfs(int i,L j,int k)
{
    if(h[i*n+j])
      return h[i*n+j]*k;
    if(i==0)
      return j*k;
    L p;
    p=dfs(i-1,j,k);
    if(x[i]<=j)
      p+=dfs(i-1,j/x[i],-k);
    h[i*n+j]=k*p;
    return p;
}
inline U power(U a,int b)
{
    if(!b)
      return 1;
    U c=power(a,b>>1);
    c=c*c;
    if(b&1)
      c=c*a;
    return c;
}
int main()
{
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	int i,j,k;
	scanf("%lld%d",&n,&k);
    m=sqrt(n)+1;
    for(i=2;i<=m;i++)
      {
       for(j=2;j*j<=i;j++)
         if(i%j==0)
           break;
       if(j*j>i)
         x[++q]=i;
      }
    for(i=1;i<=q && i<=t;i++)
      p+=(dfs(i-1,n/x[i],1)-1)*power(x[i],k);
    if(q>t)
      {
       s=a=n/x[t+1];
       for(i=1;i<=t;i++)
         for(j=x[i];j<=a;j+=x[i])
           if(!w[j])
             {
              w[j]=1;
              s--;
             }
       for(i=t+1;i<=q;i++)
         {
          p+=(s-1)*power(x[i],k);
          if(i<q)
            {
             a=n/x[i+1];
             for(j=n/x[i];j>a;j--)
               if(!w[j])
                 s--;
             for(j=x[i];j<=a;j+=x[i])
               if(!w[j])
                 {
                  w[j]=1;
                  s--;
                 }
            }
         }
      }
    cout<<p<<"\n";
	return 0;
}

