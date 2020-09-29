#include<cstdio>
#include<cctype>
#include<set>
using namespace std;
const int N=2e5;
int n,fa[N+1],cnt[N+1][2];
auto cmp=[](const int x,const int y)->bool {
	return 1ll*cnt[x][0]*cnt[y][1]==1ll*cnt[y][0]*cnt[x][1]?x>y:1ll*cnt[x][0]*cnt[y][1]>1ll*cnt[y][0]*cnt[x][1];
};
auto s=set<int,decltype(cmp)>(cmp);
long long res;
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
namespace union_set {
	int fa[N+1];
	int find(int x)
	{
		return fa[x]?fa[x]=find(fa[x]):x;
	}
	inline void merge(int x,int y)
	{
		fa[y]=x;
		return;
	}
}
int main()
{
	n=read();
	for(int i=2;i<=n;++i) {
		fa[i]=read();
	}
	for(int i=1;i<=n;++i) {
		cnt[i][read()]=1;
	}
	for(int i=2;i<=n;++i) {
		s.insert(i);
	}
	while(!s.empty()) {
		int u=union_set::find(*s.begin()),f=union_set::find(fa[u]);
		s.erase(u),s.erase(f);
		res+=1ll*cnt[u][0]*cnt[f][1];
		union_set::merge(f,u);
		cnt[f][0]+=cnt[u][0],cnt[f][1]+=cnt[u][1];
		if(f!=1) {
			s.insert(f);
		}
	}
	printf("%lld\n",res);
	return 0;
}
