#include<cstdio>
#include<cctype>
#include<vector>
using namespace std;
const int N=5e5;
int n,m;
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
void getUpper(char &x)
{
	do {
		x=getchar();
	} while(!isupper(x));
	return;
}
class unionSet {
private:
	int fa[N+1],siz[N+1],mergeTim[N+1];
public:
	inline void init()
	{
		fill_n(siz+1,n,1);
		return;
	}
	inline bool isRoot(int x)
	{
		return !fa[x];
	}
	inline int getFa(int x)
	{
		return fa[x];
	}
	inline int getSiz(int x)
	{
		return siz[x];
	}
	inline int getMergeTim(int x)
	{
		return mergeTim[x];
	}
	int find(int x)
	{
		while(!isRoot(x)) {
			x=fa[x];
		}
		return x;
	}
	void merge(int u,int v,int t)
	{
		u=find(u),v=find(v);
		if(siz[u]<siz[v]) {
			swap(u,v);
		}
		fa[v]=u,siz[u]+=siz[v],mergeTim[v]=t;
		return;
	}
} uni,mil;
vector<pair<int,long long>> sum[N+1];
int resetTim[N+1];
int main()
{
	read(n),read(m);
	uni.init(),mil.init();
	for(int i=1;i<=n;++i) {
		sum[i].push_back(make_pair(-1,0));
	}
	for(int i=1;i<=m;++i) {
		char opt;
		getUpper(opt);
		switch(opt) {
			case 'U': {
				int u,v;
				read(u),read(v);
				uni.merge(u,v,i);
				break;
			}
			case 'M': {
				int u,v;
				read(u),read(v);
				mil.merge(u,v,i);
				break;
			}
			case 'A': {
				int u;
				read(u);
				u=uni.find(u);
				sum[u].push_back(make_pair(i,sum[u].back().second+uni.getSiz(u)));
				break;
			}
			case 'Z': {
				int u;
				read(u);
				u=mil.find(u);
				resetTim[u]=i;
				break;
			}
			case 'Q': {
				int x;
				long long r;
				read(x);
				int nx=x,lasResetTim=resetTim[x];
				while(!mil.isRoot(nx)) {
					int nf=mil.getFa(nx);
					if(mil.getMergeTim(nx)<resetTim[nf]) {
						lasResetTim=max(lasResetTim,resetTim[nf]);
					}
					nx=nf;
				}
				nx=x;
				int p=distance(sum[x].begin(),lower_bound(sum[x].begin(),sum[x].end(),make_pair(lasResetTim,0ll)));
				r=sum[x].back().second-sum[x][p-1].second;
				while(!uni.isRoot(nx)) {
					int nf=uni.getFa(nx);
					p=distance(sum[nf].begin(),lower_bound(sum[nf].begin(),sum[nf].end(),make_pair(max(lasResetTim,uni.getMergeTim(nx)),0ll)));
					r+=sum[nf].back().second-sum[nf][p-1].second;
					nx=nf;
				}
				printf("%I64d\n",r);
				break;
			}
		}
	}
	return 0;
}
