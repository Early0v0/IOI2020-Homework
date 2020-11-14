#include<cstdio>
#include<cctype>
#define For(i,l,r) for(int i=l;i<=r;++i)
using namespace std;
const int N=5000;
const long long inf=0x3f3f3f3f3f3f3f3f;
int n,s,e;
int x[N+1],a[N+1],b[N+1],c[N+1],d[N+1];
int nex[N+1];
long long res;
int read()
{
	int ret=0;
	char c=getchar();
	while(!isdigit(c)) {
		c=getchar();
	}
	while(isdigit(c)) {
		ret=ret*10+c-'0';
		c=getchar();
	}
	return ret;
}
inline long long calc(int u,int v)
{
	return u<v?(long long)x[v]-x[u]+d[u]+a[v]:(long long)x[u]-x[v]+c[u]+b[v];
}
int main()
{
	n=read(),s=read(),e=read();
	For(i,1,n) {
		x[i]=read();
	}
	For(i,1,n) {
		a[i]=read();
	}
	For(i,1,n) {
		b[i]=read();
	}
	For(i,1,n) {
		c[i]=read();
	}
	For(i,1,n) {
		d[i]=read();
	}
	nex[s]=e,res=calc(s,e);
	For(i,1,n) {
		if((i==s)||(i==e)) {
			continue;
		}
		int p;
		long long v=inf;
		for(int j=s;j!=e;j=nex[j]) {
			long long tem=calc(j,i)+calc(i,nex[j])-calc(j,nex[j]);
			if(tem<v) {
				p=j,v=tem;
			}
		}
		nex[i]=nex[p],nex[p]=i;
		res+=v;
	}
	printf("%I64d\n",res);
	return 0;
}
