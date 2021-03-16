#include<cstdio>
#include<cctype>
#include<vector>
using namespace std;
const int N=1e5;
int n;
vector<int> e[N+1];
char c[N+2];
int rt,cnt,dia;
int deg[N+1],w[N+1],f[N+1];
bool vis[N+1];
int res;
void read(int &x)
{
	char c;
	x=0;
	do {
		c=getchar();
	} while(isspace(c));
	do {
		x=x*10+c-'0';
		c=getchar();
	} while(isdigit(c));
	return;
}
void dfs(int u,int fa)
{
	deg[u]=u!=rt;
	vis[u]=c[u]=='W';
	for(int v:e[u]) {
		if(v==fa) {
			continue;
		}
		dfs(v,u);
		if(vis[v]) {
			++deg[u];
		}
		vis[u]|=vis[v];
	}
	if(!vis[u]) {
		return;
	}
	cnt+=2;
	if((deg[u]&1)^(c[u]=='W')) {
		w[u]=2,++cnt;
	}
	f[u]=w[u];
	for(int v:e[u]) {
		if(v==fa) {
			continue;
		}
		dia=max(dia,f[u]+f[v]);
		f[u]=max(f[u],f[v]+w[u]);
	}
	return;
}
int main()
{
	read(n);
	for(int i=1,u,v;i<n;++i) {
		read(u),read(v);
		e[u].push_back(v),e[v].push_back(u);
	}
	scanf("%s",c+1);
	for(int i=1;i<=n;++i) {
		if(c[i]=='W') {
			rt=i,++cnt;
		}
	}
	switch(cnt) {
		case 0: {
			res=0;
			break;
		}
		case 1: {
			res=1;
			break;
		}
		default: {
			cnt=0;
			dfs(rt,0);
			res=cnt-dia-2;
			break;
		}
	}
	printf("%d\n",res);
	return 0;
}
