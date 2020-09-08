#include<cstdio>
#include<cctype>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1e5;
typedef pair<int,int> pii;
int n,q;
vector<pii>e[N+1];
int rt1,rt2;
long long dis1[N+1],dis2[N+1];
struct node {
	int id;
	long long maxdis;
};
node p[N+1];
bool vis[N+1];
int res;
template<class T>T read()
{
	T ret=0;
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
void dfs(int u,int fa,long long dis[])
{
	for(pii edg:e[u]) {
		int v=edg.first;
		if(v==fa) {
			continue;
		}
		dis[v]=dis[u]+edg.second;
		dfs(v,u,dis);
	}
	return;
}
namespace unionset {
	int fa[N+1],siz[N+1];
	inline void init()
	{
		fill(fa+1,fa+n+1,0);
		fill(siz+1,siz+n+1,1);
		return;
	}
	int find(int x)
	{
		return fa[x]?fa[x]=find(fa[x]):x;
	}
	void merge(int x,int y)
	{
		x=find(x),y=find(y);
		if(x!=y) {
			fa[y]=x,siz[x]+=siz[y];
			res=max(res,siz[x]);
		}
		return;
	}
}
int main()
{
	n=read<int>();
	for(int i=1,u,v,w;i<n;++i) {
		u=read<int>(),v=read<int>(),w=read<int>();
		e[u].push_back(pii{v,w}),e[v].push_back(pii{u,w});
	}
	dfs(1,0,dis1);
	for(int i=1;i<=n;++i) {
		rt1=dis1[i]>dis1[rt1]?i:rt1;
	}
	dis1[rt1]=0,dfs(rt1,0,dis1);
	for(int i=1;i<=n;++i) {
		rt2=dis1[i]>dis1[rt2]?i:rt2;
	}
	dfs(rt2,0,dis2);
	for(int i=1;i<=n;++i) {
		p[i]=node{i,max(dis1[i],dis2[i])};
	}
	sort(p+1,p+n+1,[](const node x,const node y) {
		return x.maxdis>y.maxdis;
	});
	for(int q=read<int>();q;--q) {
		unionset::init();
		long long len=read<long long>();
		res=1;
		for(int l=1,r=0;l<=n;++l) {
			while((r<n)&&(p[l].maxdis-p[r+1].maxdis<=len)) {
				int u=p[++r].id;
				vis[u]=true;
				for(pii edg:e[u]) {
					int v=edg.first;
					if(vis[v]) {
						unionset::merge(u,v);
					}
				}
			}
			--unionset::siz[unionset::find(p[l].id)],vis[p[l].id]=false;
		}
		printf("%d\n",res);
	}
	return 0;
}
