#include<cstdio>
#include<cctype>
#include<vector>
#include<cstdlib>
using namespace std;
const int N=1e5,inf=0x3f3f3f3f;
int n,m,tl,tr;
int l[N+1],r[N+1];
vector<int>e[N+1];
int p1=inf,p2;
int col[N+1];
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
inline bool contain(int x,int v)
{
	return (v>=l[x])&&(v<=r[x]);
}
bool dfs(int u)
{
	for(int v:e[u]) {
		if(col[v]) {
			if(col[v]==col[u]) {
				return false;
			}
		} else {
			col[v]=col[u]^3;
			if(!dfs(v)) {
				return false;
			}
		}
	}
	return true;
}
namespace output {
	inline void impossible()
	{
		puts("IMPOSSIBLE");
		exit(0);
	}
	void possible()
	{
		puts("POSSIBLE");
		printf("%d %d\n",p1,p2);
		for(int i=1;i<=n;++i) {
			putchar(col[i]+'0');
		}
		putchar('\n');
		return;
	}
}
int main()
{
	tl=read(),tr=read();
	n=read(),m=read();
	for(int i=1;i<=n;++i) {
		l[i]=read(),r[i]=read();
	}
	for(int i=1,u,v;i<=m;++i) {
		u=read(),v=read();
		e[u].push_back(v),e[v].push_back(u);
	}
	for(int i=1;i<=n;++i) {
		p1=min(p1,r[i]),p2=max(p2,l[i]);
	}
	if(p1+p2<tl) {
		p2=tl-p1;
	}
	if(p1+p2>tr) {
		p1=tr-p2;
	}
	if((p1<0)||(p2<0)) {
		output::impossible();
	}
	for(int i=1;i<=n;++i) {
		bool c1=contain(i,p1),c2=contain(i,p2);
		if(!c1&&!c2) {
			output::impossible();
		}
		if(!c1||!c2) {
			col[i]=c1?1:2;
		}
	}
	for(int i=1;i<=n;++i) {
		if(col[i]) {
			if(!dfs(i)) {
				output::impossible();
			}
		}
	}
	for(int i=1;i<=n;++i) {
		if(!col[i]) {
			col[i]=1;
			if(!dfs(i)) {
				output::impossible();
			}
		}
	}
	output::possible();
	return 0;
}
