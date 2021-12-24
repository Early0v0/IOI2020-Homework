#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
const int N=80,M=320,X=100,inf=0x3f3f3f3f;
const long long infll=0x3f3f3f3f3f3f3f3f;
int n,m;
struct point {
	int x,y;
	long long v;
} p[N+1];
struct request {
	char t;
	int b,c;
} r[M+1];
long long res;
namespace MCMF {
	const int P=N*4+2,E=N*N*2+N*3,S=1,T=2;
	int cp,ce,fir[P+1];
	struct edge {
		int v,w;
		long long c;
		int nex;
	} e[E*2+2];
	long long d[P+1];
	int nfir[P+1];
	long long cost;
	void init(int _cp)
	{
		cp=_cp,ce=1;
		fill_n(fir+1,cp,0);
		cost=0;
		return;
	}
	void addEdge(int u,int v,int w,long long c)
	{
		e[++ce]=edge{v,w,c,fir[u]},fir[u]=ce;
		e[++ce]=edge{u,0,-c,fir[v]},fir[v]=ce;
		return;
	}
	bool spfa()
	{
		static queue<int> q;
		static bool inq[P+1];
		fill_n(d+1,cp,infll);
		d[S]=0;
		q.push(S),inq[S]=true;
		while(!q.empty()) {
			int u=q.front();
			q.pop(),inq[u]=false;
			for(int i=fir[u],v;v=e[i].v,i;i=e[i].nex) {
				if(e[i].w&&(d[v]>d[u]+e[i].c)) {
					d[v]=d[u]+e[i].c;
					if(!inq[v]) {
						q.push(v),inq[v]=true;
					}
				}
			}
		}
		return d[T]!=infll;
	}
	int dfs(int u,int f)
	{
		static bool vis[P+1];
		if(u==T) {
			return f;
		}
		int r=f;
		vis[u]=true;
		for(int &i=nfir[u],v;v=e[i].v,i&&r;i=e[i].nex) {
			if(!vis[v]&&e[i].w&&(d[v]==d[u]+e[i].c)) {
				int t=dfs(v,min(r,e[i].w));
				e[i].w-=t,e[i^1].w+=t,r-=t,cost+=e[i].c*t;
			}
		}
		vis[u]=false;
		return f-r;
	}
	int flow()
	{
		int r=0;
		while(spfa()) {
			copy_n(fir+1,cp,nfir+1);
			while(int t=dfs(S,inf)) {
				r+=t;
			}
		}
		return r;
	}
}
long long calc(int k)
{
	static int lx[N+1],rx[N+1],ly[N+1],ry[N+1];
	MCMF::init(n*2+k*2+2);
	fill_n(lx+1,k,0),fill_n(rx+1,k,X);
	fill_n(ly+1,k,0),fill_n(ry+1,k,X);
	for(int i=1;i<=m;++i) {
		if(r[i].c>=k) {
			continue;
		}
		switch(r[i].t) {
			case 'L': {
				lx[r[i].c+1]=max(lx[r[i].c+1],r[i].b+1);
				break;
			}
			case 'R': {
				rx[k-r[i].c]=min(rx[k-r[i].c],r[i].b-1);
				break;
			}
			case 'D': {
				ly[r[i].c+1]=max(ly[r[i].c+1],r[i].b+1);
				break;
			}
			case 'U': {
				ry[k-r[i].c]=min(ry[k-r[i].c],r[i].b-1);
				break;
			}
		}
	}
	for(int i=2;i<=k;++i) {
		lx[i]=max(lx[i],lx[i-1]),ly[i]=max(ly[i],ly[i-1]);
	}
	for(int i=k-1;i;--i) {
		rx[i]=min(rx[i],rx[i+1]),ry[i]=min(ry[i],ry[i+1]);
	}
	for(int i=1;i<=k;++i) {
		MCMF::addEdge(MCMF::S,i+n*2+2,1,0);
		for(int j=1;j<=n;++j) {
			if((p[j].x>=lx[i])&&(p[j].x<=rx[i])) {
				MCMF::addEdge(i+n*2+2,j+2,1,0);
			}
		}
	}
	for(int i=1;i<=n;++i) {
		MCMF::addEdge(i+2,i+n+2,1,-p[i].v);
	}
	for(int i=1;i<=k;++i) {
		for(int j=1;j<=n;++j) {
			if((p[j].y>=ly[i])&&(p[j].y<=ry[i])) {
				MCMF::addEdge(j+n+2,i+n*2+k+2,1,0);
			}
		}
		MCMF::addEdge(i+n*2+k+2,MCMF::T,1,0);
	}
	if(MCMF::flow()==k) {
		return -MCMF::cost;
	} else {
		return 0;
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;++i) {
		cin>>p[i].x>>p[i].y>>p[i].v;
	}
	cin>>m;
	for(int i=1;i<=m;++i) {
		cin>>r[i].t>>r[i].b>>r[i].c;
	}
	for(int i=1;i<=n;++i) {
		res=max(res,calc(i));
	}
	cout<<res<<endl;
	return 0;
}
