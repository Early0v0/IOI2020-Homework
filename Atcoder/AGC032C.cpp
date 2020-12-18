#include<cstdio>
#include<cctype>
#include<vector>
#include<cstdlib>
using namespace std;
const int N=1e5;
int n,m;
vector<int>e[N+1];
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
bool dfs(int u,int f,int p)
{
	for(int v:e[u]) {
		if(v==f) {
			continue;
		}
		if(v==p) {
			return true;
		}
		if((e[v].size()==2)&&dfs(v,u,p)) {
			return true;
		}
	}
	return false;
}
namespace output {
	inline void yes()
	{
		puts("Yes");
		exit(0);
	}
	inline void no()
	{
		puts("No");
		exit(0);
	}
}
int main()
{
	n=read(),m=read();
	for(int i=1,u,v;i<=m;++i) {
		u=read(),v=read();
		e[u].push_back(v),e[v].push_back(u);
	}
	for(int i=1;i<=n;++i) {
		if(e[i].size()&1) {
			output::no();
		}
	}
	for(int i=1;i<=n;++i) {
		if(e[i].size()>=6) {
			output::yes();
		}
	}
	int cnt=0;
	for(int i=1;i<=n;++i) {
		cnt+=e[i].size()==4;
	}
	switch(cnt) {
		case 0: case 1: {
			output::no();
		}
		case 2: {
			for(int i=1;i<=n;++i) {
				if(e[i].size()==4) {
					if(dfs(i,0,i)) {
						output::yes();
					}
				}
			}
			output::no();
		}
		default: {
			output::yes();
		}
	}
	return 0;
}
