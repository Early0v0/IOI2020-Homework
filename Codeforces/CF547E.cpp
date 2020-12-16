#include<cstdio>
#include<cctype>
#include<vector>
#include<queue>
using namespace std;
const int N=2e5,C=26,S=2e5,Q=5e5;
typedef pair<int,int> pii;
int n,m;
int k[Q+1];
vector<pii>q[N+1];
int res[Q+1];
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
namespace AC_Automaton {
	struct tree {
		int fa,son[C],fail;
		int siz,dfn;
	};
	int cnt=1;
	tree t[S+1];
	int pos[N+1];
	vector<int>e[S+1];
	void insert(char s[],int p)
	{
		int x=1;
		for(char *it=s,c;c=*it-'a',*it;++it) {
			if(!t[x].son[c]) {
				t[x].son[c]=++cnt;
				t[cnt].fa=x;
			}
			x=t[x].son[c];
		}
		pos[p]=x;
		return;
	}
	void build()
	{
		static queue<int>q;
		for(int i=0;i<C;++i) {
			if(t[1].son[i]) {
				t[t[1].son[i]].fail=1;
				q.push(t[1].son[i]);
			} else {
				t[1].son[i]=1;
			}
		}
		while(!q.empty()) {
			int x=q.front();
			q.pop();
			for(int i=0;i<C;++i) {
				if(t[x].son[i]) {
					t[t[x].son[i]].fail=t[t[x].fail].son[i];
					q.push(t[x].son[i]);
				} else {
					t[x].son[i]=t[t[x].fail].son[i];
				}
			}
		}
		for(int i=2;i<=cnt;++i) {
			e[t[i].fail].push_back(i);
		}
		return;
	}
	void dfs(int u)
	{
		static int tot;
		t[u].dfn=++tot,t[u].siz=1;
		for(int v:e[u]) {
			dfs(v);
			t[u].siz+=t[v].siz;
		}
		return;
	}
}
namespace BIT {
	using AC_Automaton::cnt;
	int t[S+1];
	inline int lowbit(int x)
	{
		return x&-x;
	}
	void update(int x)
	{
		do {
			++t[x];
		} while((x+=lowbit(x))<=cnt);
		return;
	}
	int query(int x)
	{
		int ret=0;
		do {
			ret+=t[x];
		} while(x-=lowbit(x));
		return ret;
	}
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;++i) {
		static char s[S+1];
		scanf("%s",s);
		AC_Automaton::insert(s,i);
	}
	AC_Automaton::build();
	AC_Automaton::dfs(1);
	for(int i=1;i<=m;++i) {
		q[read()-1].push_back(pii{i,-1});
		q[read()].push_back(pii{i,1});
		k[i]=read();
	}
	for(int i=1;i<=n;++i) {
		using namespace AC_Automaton;
		int x=pos[i];
		while(x!=1) {
			BIT::update(t[x].dfn);
			x=t[x].fa;
		}
		for(pii j:q[i]) {
			int p=j.first,x=pos[k[p]];
			res[p]+=j.second*(BIT::query(t[x].dfn+t[x].siz-1)-BIT::query(t[x].dfn-1));
		}
	}
	for(int i=1;i<=m;++i) {
		printf("%d\n",res[i]);
	}
	return 0;
}
