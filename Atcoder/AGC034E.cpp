#include<cstdio>
#include<cctype>
#include<vector>
using namespace std;
const int N=2000,inf=0x3f3f3f3f;
int n,val[N+1];
vector<int>e[N+1];
int siz[N+1],dis[N+1],f[N+1];
int res=inf;
void dfs(int u,int fa)
{
	siz[u]=val[u],dis[u]=0;
	int maxn=0;
	for(int v:e[u]) {
		if(v==fa) {
			continue;
		}
		dfs(v,u);
		siz[u]+=siz[v],dis[u]+=dis[v];
		if(dis[v]>=dis[maxn]) {
			maxn=v;
		}
	}
	if(maxn) {
		if(dis[u]>=dis[maxn]*2) {
			f[u]=dis[u]/2;
		} else {
			f[u]=dis[u]-dis[maxn]+min(f[maxn],(dis[maxn]*2-dis[u])/2);
		}
	} else {
		f[u]=0;
	}
	if(fa) {
		dis[u]+=siz[u];
	}
	return;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) {
		char c=getchar();
		while(!isdigit(c)) {
			c=getchar();
		}
		val[i]=c-'0';
	}
	for(int i=1,u,v;i<n;++i) {
		scanf("%d%d",&u,&v);
		e[u].push_back(v),e[v].push_back(u);
	}
	for(int i=1;i<=n;++i) {
		dfs(i,0);
		if(!(dis[i]&1)&&(f[i]>=dis[i]/2)) {
			res=min(res,dis[i]/2);
		}
	}
	printf("%d\n",res==inf?-1:res);
	return 0;
}