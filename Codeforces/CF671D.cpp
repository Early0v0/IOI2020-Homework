#include<cstdio>
#include<cctype>
#include<vector>
#include<cstdlib>
using namespace std;
const int N=3e5,M=3e5;
typedef pair<int,int> pii;
typedef pair<int,long long> pil;
int n,m;
vector<int>e[N+1];
int dep[N+1];
vector<pii>p[N+1];
long long f[N+1],res;
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
namespace leftist_tree {
	struct tree {
		pil val;
		long long tag;
		int dis;
		tree *fa,*lson,*rson;
		tree(pil v)
		{
			val=v,tag=0,dis=1;
			fa=lson=rson=nullptr;
			return;
		}
	};
	tree *rt[M+1];
	inline void modify(tree *x,long long v)
	{
		if(x) {
			x->val.second+=v,x->tag+=v;
		}
		return;
	}
	void push_down(tree *x)
	{
		if(!x->tag) {
			return;
		}
		modify(x->lson,x->tag),modify(x->rson,x->tag);
		x->tag=0;
		return;
	}
	tree *merge(tree *x,tree *y)
	{
		if(!x||!y) {
			return x!=nullptr?x:y;
		}
		if(x->val.second>y->val.second) {
			swap(x,y);
		}
		push_down(x);
		x->rson=merge(x->rson,y),x->rson->fa=x;
		if(!x->lson||x->lson->dis<x->rson->dis) {
			swap(x->lson,x->rson);
		}
		x->dis=x->rson?x->rson->dis+1:1;
		return x;
	}
}
inline void fail()
{
	puts("-1");
	exit(0);
}
void dfs(int u,int fa)
{
	using namespace leftist_tree;
	dep[u]=dep[fa]+1;
	for(pii i:p[u]) {
		rt[u]=merge(rt[u],new tree(i));
	}
	long long sum=0;
	for(int v:e[u]) {
		if(v==fa) {
			continue;
		}
		dfs(v,u);
		sum+=f[v];
		modify(rt[v],-f[v]);
		rt[u]=merge(rt[u],rt[v]);
	}
	modify(rt[u],sum);
	while(rt[u]&&(dep[rt[u]->val.first]>=dep[u])) {
		push_down(rt[u]);
		rt[u]=merge(rt[u]->lson,rt[u]->rson);
	}
	if(!rt[u]) {
		fail();
		return;
	}
	f[u]=rt[u]->val.second;
	return;
}
int main()
{
	n=read(),m=read();
	for(int i=1,u,v;i<n;++i) {
		u=read(),v=read();
		e[u].push_back(v),e[v].push_back(u);
	}
	for(int i=1,u,v,w;i<=m;++i) {
		u=read(),v=read(),w=read();
		p[u].push_back(pii{v,w});
	}
	for(int i:e[1]) {
		dfs(i,1);
		res+=f[i];
	}
	printf("%I64d\n",res);
	return 0;
}
