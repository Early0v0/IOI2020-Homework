#include<cstdio>
#include<cctype>
#include<vector>
using namespace std;
const int N=3e5,L=19;
int n,c[N+1];
vector<int>e[N+1];
int fa[L+1][N+1],cnt,dfn[N+1],rnk[N*2],dep[N+1],maxdep[N+1];
int son[N+1],top[N+1];
int len[N+1],*up[N+1],*down[N+1];
int lg2[N*2];
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
int inv(int x,const int mod)
{
	int times=mod-2,ret=1;
	while(times) {
		if(times&1) {
			ret=1ll*ret*x%mod;
		}
		times>>=1,x=1ll*x*x%mod;
	}
	return ret;
}
namespace Hash {
	const int mod1=1e9+7,mod2=1e9+9;
	int pow1[N+1],pow2[N+1],inv1[N+1],inv2[N+1];
	struct data {
		int len;
		int v1,v2;
		inline void push_front(int c)
		{
			v1=(v1+1ll*pow1[len]*c)%mod1,v2=(v2+1ll*pow2[len]*c)%mod2,++len;
			return;
		}
		inline void push_back(int c)
		{
			v1=(26ll*v1+c)%mod1,v2=(26ll*v2+c)%mod2,++len;
			return;
		}
	};
	data h1[N+1],h2[N+1];
	void init()
	{
		const int inv26_1=inv(26,mod1),inv26_2=inv(26,mod2);
		pow1[0]=pow2[0]=inv1[0]=inv2[0]=1;
		for(int i=1;i<=n;++i) {
			pow1[i]=26ll*pow1[i-1]%mod1;
			pow2[i]=26ll*pow2[i-1]%mod2;
			inv1[i]=1ll*inv26_1*inv1[i-1]%mod1;
			inv2[i]=1ll*inv26_2*inv2[i-1]%mod2;
		}
		return;
	}
	inline bool operator ==(const data x,const data y)
	{
		return (x.len==y.len)&&(x.v1==y.v1)&&(x.v2==y.v2);
	}
	inline data operator +(const data x,const data y)
	{
		return data{x.len+y.len,(1ll*pow1[y.len]*x.v1+y.v1)%mod1,(1ll*pow2[y.len]*x.v2+y.v2)%mod2};
	}
	inline data operator -(const data x,const data y)
	{
		return data{x.len,(x.v1-y.v1+mod1)%mod1,(x.v2-y.v2+mod2)%mod2};
	}
	inline data operator *(const data x,const int y)
	{
		return data{x.len+y,1ll*x.v1*pow1[y]%mod1,1ll*x.v2*pow2[y]%mod2};
	}
	inline data operator /(const data x,const int y)
	{
		return data{x.len-y,1ll*x.v1*inv1[y]%mod1,1ll*x.v2*inv2[y]%mod2};
	}
}
using Hash::h1;
using Hash::h2;
void dfs1(int u,int fa)
{
	dfn[u]=++cnt,rnk[cnt]=u;
	::fa[0][u]=fa,maxdep[u]=dep[u]=dep[fa]+1;
	h1[u]=h1[fa],h1[u].push_front(c[u]);
	h2[u]=h2[fa],h2[u].push_back(c[u]);
	for(int v:e[u]) {
		if(v==fa) {
			continue;
		}
		dfs1(v,u);
		maxdep[u]=max(maxdep[u],maxdep[v]);
		son[u]=maxdep[v]>maxdep[son[u]]?v:son[u];
		rnk[++cnt]=u;
	}
	return;
}
void dfs2(int u,int top)
{
	::top[u]=top,++len[top];
	if(!son[u]) {
		return;
	}
	dfs2(son[u],top);
	for(int v:e[u]) {
		if((v!=fa[0][u])&&(v!=son[u])) {
			dfs2(v,v);
		}
	}
	return;
}
void pretreatment()
{
	for(int l=1;l<=L;++l) {
		for(int i=1;i<=n;++i) {
			fa[l][i]=fa[l-1][fa[l-1][i]];
		}
	}
	for(int i=1;i<=n;++i) {
		if(top[i]!=i) {
			continue;
		}
		up[i]=new int[len[i]],down[i]=new int[len[i]];
		for(int j=0,pos=i;(j<len[i])&&pos;++j,pos=fa[0][pos]) {
			up[i][j]=pos;
		}
		for(int j=0,pos=i;j<len[i];++j,pos=son[pos]) {
			down[i][j]=pos;
		}
	}
	return;
}
int kthfa(int u,int k)
{
	if(dep[u]<=k) {
		return 0;
	}
	if(!k) {
		return u;
	}
	int l=lg2[k];
	u=fa[l][u],k^=1<<l;
	int delta=dep[u]-dep[top[u]];
	return delta<=k?up[top[u]][k-delta]:down[top[u]][delta-k];
}
namespace ST {
	int st[L+1][N*2];
	void build()
	{
		for(int i=1;i<=cnt;++i) {
			st[0][i]=rnk[i];
		}
		for(int l=1;l<=L;++l) {
			for(int i=1;i+(1<<l)-1<=cnt;++i) {
				int x=st[l-1][i],y=st[l-1][i+(1<<l-1)];
				st[l][i]=dep[x]<=dep[y]?x:y;
			}
		}
		return;
	}
	int lca(int u,int v)
	{
		if(dfn[u]>dfn[v]) {
			swap(u,v);
		}
		int l=lg2[dfn[v]-dfn[u]+1],x=st[l][dfn[u]],y=st[l][dfn[v]-(1<<l)+1];
		return dep[x]<=dep[y]?x:y;
	}
}
Hash::data path(int u,int v,int lca,int l)
{
	using namespace Hash;
	data ret;
	int l1=min(l,dep[u]-dep[lca]+1),ancu=kthfa(u,l1);
	ret=(h1[u]-h1[ancu])/dep[ancu];
	if(l1==l) {
		return ret;
	}
	int l2=l-l1,ancv=kthfa(v,dep[v]-dep[lca]-l2);
	data tem=h2[ancv]-h2[lca]*l2;
	tem.len=l2;
	ret=ret+tem;
	ret.len=l;
	return ret;
}
int main()
{
	n=read();
	for(int i=1;i<=n;++i) {
		c[i]=getchar()-'a';
	}
	for(int i=1,u,v;i<n;++i) {
		u=read(),v=read();
		e[u].push_back(v),e[v].push_back(u);
	}
	Hash::init();
	dfs1(1,0);
	dfs2(1,1);
	for(int i=2;i<=cnt;++i) {
		lg2[i]=lg2[i>>1]+1;
	}
	pretreatment();
	ST::build();
	for(int m=read();m;--m) {
		int u1=read(),v1=read(),u2=read(),v2=read();
		int lca1=ST::lca(u1,v1),lca2=ST::lca(u2,v2);
		int l=0,r=min(dep[u1]+dep[v1]-dep[lca1]*2+1,dep[u2]+dep[v2]-dep[lca2]*2+1),res=0;
		while(l<=r) {
			int mid=(l+r)/2;
			if(path(u1,v1,lca1,mid)==path(u2,v2,lca2,mid)) {
				res=mid,l=mid+1;
			} else {
				r=mid-1;
			}
		}
		printf("%d\n",res);
	}
	return 0;
}
