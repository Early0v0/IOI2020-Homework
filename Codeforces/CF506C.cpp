#include<cstdio>
#include<cctype>
#include<queue>
using namespace std;
const int N=1e5,M=5000,G=1e9;
typedef pair<long long,int> pli;
int n,m,k,p,h[N+1],g[N+1];
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
bool check(long long x)
{
	static priority_queue<pli,vector<pli>,greater<pli>>que;
	static long long nh[N+1];
	que.swap(*(new priority_queue<pli,vector<pli>,greater<pli>>));
	for(int i=1;i<=n;++i) {
		nh[i]=x;
		if(nh[i]<1ll*m*g[i]) {
			que.push(pli{x/g[i],i});
		}
	}
	long long cnt=0;
	while(!que.empty()&&(cnt<=k*m)) {
		pli t=que.top();
		que.pop();
		long long nday=cnt/k+1;
		if(t.first<nday) {
			return false;
		}
		++cnt;
		if((nh[t.second]+=p)<1ll*m*g[t.second]) {
			que.push(pli{nh[t.second],t.second});
		}
	}
	if(cnt>k*m) {
		return false;
	}
	for(int i=1;i<=n;++i) {
		if(nh[i]-1ll*m*g[i]>=h[i]) {
			continue;
		}
		cnt+=(h[i]-(nh[i]-1ll*m*g[i])+p-1)/p;
	}
	return cnt<=k*m;
}
int main()
{
	n=read(),m=read(),k=read(),p=read();
	long long l=0,r=1ll*(M+1)*G;
	for(int i=1;i<=n;++i) {
		h[i]=read(),g[i]=read();
		l=max(l,1ll*g[i]);
	}
	while(l<=r) {
		long long mid=(l+r)/2;
		if(check(mid)) {
			res=mid,r=mid-1;
		} else {
			l=mid+1;
		}
	}
	printf("%I64d\n",res);
	return 0;
}
