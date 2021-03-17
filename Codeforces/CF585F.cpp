#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1000,D=50,C=10,mod=1e9+7;
int n,d;
char s[N+1],l[D+1],r[D+1];
int res;
namespace SAM {
	struct point {
		int len;
		int fa,son[C];
	} t[N*2+1];
	int cnt,rt,las;
	inline int newPoint(int l)
	{
		t[++cnt].len=l;
		return cnt;
	}
	void insert(int c)
	{
		int p=las,np=las=newPoint(t[p].len+1);
		while(p&&!t[p].son[c]) {
			t[p].son[c]=np,p=t[p].fa;
		}
		if(!p) {
			t[np].fa=rt;
		} else {
			int q=t[p].son[c];
			if(t[q].len==t[p].len+1) {
				t[np].fa=q;
			} else {
				int nq=newPoint(t[p].len+1);
				t[nq].fa=t[q].fa,copy_n(t[q].son,C,t[nq].son);
				t[np].fa=t[q].fa=nq;
				while(p&&(t[p].son[c]==q)) {
					t[p].son[c]=nq,p=t[p].fa;
				}
			}
		}
		return;
	}
	void build(int n,char s[])
	{
		rt=las=newPoint(0);
		for(int i=0;i<n;++i) {
			insert(s[i]-'0');
		}
		return;
	}
}
int calc(char s[],int x,int p,int l,bool up,bool sat)
{
	static int f[D][N*2+1][D+1][2];
	static bool vis[D][N*2+1][D+1][2];
	if(x==d) {
		return sat;
	}
	if(!up) {
		if(vis[x][p][l][sat]) {
			return f[x][p][l][sat];
		}
		vis[x][p][l][sat]=true;
	}
	int r=0,maxDig=up?s[x]-'0':C-1;
	for(int dig=0;dig<=maxDig;++dig) {
		if(sat) {
			r=(r+calc(s,x+1,p,l,up&&(dig==maxDig),true))%mod;
		} else {
			if(SAM::t[p].son[dig]) {
				r=(r+calc(s,x+1,SAM::t[p].son[dig],l+1,up&&(dig==maxDig),l+1>=d/2))%mod;
			} else {
				int np=p;
				while(np&&!SAM::t[np].son[dig]) {
					np=SAM::t[np].fa;
				}
				if(np) {
					r=(r+calc(s,x+1,SAM::t[np].son[dig],SAM::t[np].len+1,up&&(dig==maxDig),SAM::t[np].len+1>=d/2))%mod;
				} else {
					r=(r+calc(s,x+1,SAM::rt,0,up&&(dig==maxDig),false))%mod;
				}
			}
		}
	}
	if(!up) {
		f[x][p][l][sat]=r;
	}
	return r;
}
int main()
{
	scanf("%s",s);
	n=strlen(s);
	scanf("%s%s",l,r);
	d=strlen(l);
	SAM::build(n,s);
	--l[d-1];
	for(int i=d-1;i;--i) {
		if(l[i]<'0') {
			--l[i-1],l[i]='9';
		} else {
			break;
		}
	}
	res=calc(r,0,SAM::rt,0,true,false)-calc(l,0,SAM::rt,0,true,false);
	printf("%d\n",(res+mod)%mod);
	return 0;
}
