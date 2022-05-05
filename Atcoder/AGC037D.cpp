#include<iostream>
#include<queue>
#include<cassert>
#include<algorithm>
using namespace std;
const int N=100,M=100,inf=0x3f3f3f3f;
int n,m;
int a[N+1][M+1];
namespace flow {
	const int P=N*2+2,E=N*(M+2),S=1,T=2;
	int cp,ce;
	int fir[P+1];
	struct edge {
		int v,w,nx;
	} e[E*2+2];
	int d[P+1];
	int nfir[P+1];
	inline void init(int p)
	{
		fill_n(fir+1,cp=p+2,0),ce=1;
		return;
	}
	inline int addEdge(int u,int v,int w)
	{
		e[++ce]=edge{v,w,fir[u]},fir[u]=ce;
		e[++ce]=edge{u,0,fir[v]},fir[v]=ce;
		return ce;
	}
	bool bfs()
	{
		queue<int> q;
		fill_n(d+1,cp,inf);
		d[S]=0,q.push(S);
		while(!q.empty()) {
			int u=q.front();
			q.pop();
			for(int i=fir[u],v;v=e[i].v,i;i=e[i].nx) {
				if(e[i].w&&(d[v]==inf)) {
					d[v]=d[u]+1,q.push(v);
				}
			}
		}
		return d[T]!=inf;
	}
	int dfs(int u,int f)
	{
		if(u==T) {
			return f;
		}
		int r=f;
		for(int &i=nfir[u],v;v=e[i].v,i;i=e[i].nx) {
			if(e[i].w&&(d[v]==d[u]+1)) {
				int t=dfs(v,min(r,e[i].w));
				e[i].w-=t,e[i^1].w+=t;
				if(!(r-=t)) {
					break;
				}
			}
		}
		return f-r;
	}
	int dinic()
	{
		int r=0;
		while(bfs()) {
			copy_n(fir+1,cp,nfir+1);
			while(int t=dfs(S,inf)) {
				r+=t;
			}
		}
		return r;
	}
}
int main()
{
	ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=m;++i) {
		static int id[N+1][M+1];
		flow::init(n*2);
		for(int j=1;j<=n;++j) {
			flow::addEdge(flow::S,j+2,1);
		}
		for(int j=1;j<=n;++j) {
			for(int k=i;k<=m;++k) {
				id[j][k]=flow::addEdge(j+2,(a[j][k]+m-1)/m+n+2,1);
			}
		}
		for(int j=1;j<=n;++j) {
			flow::addEdge(j+n+2,flow::T,1);
		}
		assert(flow::dinic()==n);
		for(int j=1;j<=n;++j) {
			for(int k=i;k<=m;++k) {
				if(flow::e[id[j][k]].w) {
					swap(a[j][i],a[j][k]);
					break;
				}
			}
		}
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			cout<<a[i][j]<<' ';
		}
		cout<<'\n';
	}
	for(int i=1;i<=m;++i) {
		static int v[N+1];
		for(int j=1;j<=n;++j) {
			v[j]=a[j][i];
		}
		sort(v+1,v+n+1);
		for(int j=1;j<=n;++j) {
			a[j][i]=v[j];
		}
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			cout<<a[i][j]<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
