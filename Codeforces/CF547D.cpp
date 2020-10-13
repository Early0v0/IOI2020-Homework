#include<cstdio>
#include<cctype>
#include<vector>
using namespace std;
const int N=2e5,P=2e5;
int n;
vector<int>x[P+1],y[P+1],e[N+1];
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
void dfs(int u,int c)
{
	col[u]=c;
	for(int v:e[u]) {
		if(!col[v]) {
			dfs(v,c^3);
		}
	}
	return;
}
int main()
{
	n=read();
	for(int i=1;i<=n;++i) {
		x[read()].push_back(i),y[read()].push_back(i);
	}
	for(int i=1;i<=P;++i) {
		for(auto it=x[i].begin();(it!=x[i].end())&&(it+1!=x[i].end());it+=2) {
			e[*it].push_back(*(it+1)),e[*(it+1)].push_back(*it);
		}
		for(auto it=y[i].begin();(it!=y[i].end())&&(it+1!=y[i].end());it+=2) {
			e[*it].push_back(*(it+1)),e[*(it+1)].push_back(*it);
		}
	}
	for(int i=1;i<=n;++i) {
		if(!col[i]) {
			dfs(i,1);
		}
	}
	for(int i=1;i<=n;++i) {
		putchar(col[i]==1?'r':'b');
	}
	putchar('\n');
	return 0;
}
