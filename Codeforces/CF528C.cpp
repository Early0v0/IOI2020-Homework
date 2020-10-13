#include<cstdio>
#include<cctype>
#include<vector>
using namespace std;
const int N=1e5,M=2e5;
int n,m;
int tot=1,fir[N+1];
struct edge {
	int to,nex;
	bool vis;
};
edge e[(M+N+1)*2+1];
int deg[N+1];
vector<int>v;
int res;
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
inline void add(int u,int v)
{
	e[++tot]=edge{v,fir[u],false};
	fir[u]=tot;
	return;
}
void dfs(int u)
{
	for(int &i=fir[u],v;v=e[i].to,i;i=e[i].nex) {
		if(e[i].vis) {
			continue;
		}
		e[i].vis=e[i^1].vis=true;
		dfs(v);
		if(--res&1) {
			printf("%d %d\n",u,v);
		} else {
			printf("%d %d\n",v,u);
		}
	}
	return;
}
int main()
{
	n=read(),m=read();
	for(int i=1,u,v;i<=m;++i) {
		u=read(),v=read();
		add(u,v),add(v,u);
		++deg[u],++deg[v];
	}
	res=m;
	for(int i=1;i<=n;++i) {
		if(deg[i]&1) {
			v.push_back(i);
		}
	}
	for(auto it=v.begin();it!=v.end();++++it) {
		add(*it,*(it+1)),add(*(it+1),*it);
		++res;
	}
	if(res&1) {
		add(1,1),add(1,1);
		++res;
	}
	printf("%d\n",res);
	dfs(1);
	return 0;
}
