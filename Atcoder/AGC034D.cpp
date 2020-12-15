#include<cstdio>
#include<queue>
using namespace std;
const int N=1000,P=N*2+6,E=N*10;
const int S=1,T=2,P1=3,P2=4,P3=5,P4=6;
const int inf=0x3f3f3f3f;
const long long infll=0x3f3f3f3f3f3f3f3f;
typedef pair<int,long long> pil;
int n;
struct edge {
	int v,w,c,nex;
};
int fir[P+1],nfir[P+1];
edge e[E*2+1];
long long res;
void add(int u,int v,int w,int c)
{
	static int tot=1;
	e[++tot]=edge{v,w,c,fir[u]};
	fir[u]=tot;
	return;
}
inline void addEdge(int u,int v,int w,int c)
{
	add(u,v,w,c),add(v,u,0,-c);
	return;
}
long long dis[P+1];
bool vis[P+1];
bool bfs()
{
	static queue<int>q;
	static bool inq[P+1];
	fill(dis+1,dis+n*2+7,infll);
	q.push(S),dis[S]=0,inq[S]=true;
	while(!q.empty()) {
		int u=q.front();
		q.pop(),inq[u]=false;
		for(int i=fir[u],v,c;v=e[i].v,c=e[i].c,i;i=e[i].nex) {
			if(e[i].w&&(dis[u]+c<dis[v])) {
				dis[v]=dis[u]+c;
				if(!inq[v]) {
					q.push(v),inq[v]=true;
				}
			}
		}
	}
	return dis[T]!=infll;
}
pil dfs(int u,int f)
{
	if(!f||(u==T)) {
		return pil{f,0};
	}
	vis[u]=true;
	int r=f;
	long long ret=0;
	for(int &i=nfir[u],v,c;v=e[i].v,c=e[i].c,i;i=e[i].nex) {
		if(!vis[v]&&(dis[v]==dis[u]+c)) {
			pil tem=dfs(v,min(r,e[i].w));
			r-=tem.first,ret+=1ll*tem.first*c+tem.second;
			e[i].w-=tem.first,e[i^1].w+=tem.first;
		}
	}
	vis[u]=false;
	return pil{f-r,ret};
}
long long dinic()
{
	long long ret=0;
	while(bfs()) {
		copy(fir+1,fir+n*2+7,nfir+1);
		fill(vis+1,vis+n*2+7,false);
		while(long long tem=dfs(S,inf).second) {
			ret+=tem;
		}
	}
	return ret;
}
int main()
{
	freopen("pig.in","r",stdin);
	freopen("pig.out","w",stdout);
	scanf("%d",&n);
	for(int i=1,x,y,c;i<=n;++i) {
		scanf("%d%d%d",&x,&y,&c);
		addEdge(S,i+6,c,0);
		addEdge(i+6,P1,inf,x+y),addEdge(i+6,P2,inf,x-y),addEdge(i+6,P3,inf,-x+y),addEdge(i+6,P4,inf,-x-y);
	}
	for(int i=1,x,y,c;i<=n;++i) {
		scanf("%d%d%d",&x,&y,&c);
		addEdge(i+n+6,T,c,0);
		addEdge(P1,i+n+6,inf,-x-y),addEdge(P2,i+n+6,inf,-x+y),addEdge(P3,i+n+6,inf,x-y),addEdge(P4,i+n+6,inf,x+y);
	}
	res=-dinic();
	printf("%lld\n",res);
	return 0;
}