#include<cstdio>
#include<vector>
#include<algorithm>
#define fir first
#define sec second
using namespace std;
const int K=7,N=1000;
typedef pair<int,int> pii;
int k,n;
pii a[K+1],m[N+1];
vector<int>v[K+1][N+1];
int p[K+1];
bool vis[N+1];
int res;
bool block(pii x,pii y,pii z)
{
	if(y==z) {
		return false;
	}
	if((z.fir<min(x.fir,y.fir))||(z.fir>max(x.fir,y.fir))) {
		return false;
	}
	if((z.sec<min(x.sec,y.sec))||(z.sec>max(x.sec,y.sec))) {
		return false;
	}
	return 1ll*(y.sec-x.sec)*(z.fir-x.fir)==1ll*(z.sec-x.sec)*(y.fir-x.fir);
}
int cnt;
bool dfs(int x)
{
	if(cnt>k) {
		return false;
	}
	for(int y:v[p[cnt]][x]) {
		if(vis[y]) {
			continue;
		}
		++cnt;
		if(!dfs(y)) {
			return false;
		}
	}
	vis[x]=true;
	return true;
}
int main()
{
	scanf("%d%d",&k,&n);
	for(int i=1;i<=k;++i) {
		scanf("%d%d",&a[i].fir,&a[i].sec);
	}
	for(int i=1;i<=n;++i) {
		scanf("%d%d",&m[i].fir,&m[i].sec);
	}
	for(int i=1;i<=k;++i) {
		for(int j=1;j<=n;++j) {
			for(int k=1;(k<=n)&&(v[i][j].size()<::k);++k) {
				if(block(a[i],m[j],m[k])) {
					v[i][j].push_back(k);
				}
			}
		}
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=k;++j) {
			p[j]=j;
		}
		do {
			fill(vis+1,vis+n+1,false);
			if(cnt=1,dfs(i)) {
				++res;
				break;
			}
		} while(next_permutation(p+1,p+k+1));
	}
	printf("%d\n",res);
	return 0;
}
