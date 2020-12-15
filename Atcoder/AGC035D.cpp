#include<cstdio>
#include<algorithm>
#include<random>
#include<ctime>
using namespace std;
const int N=18,T=1000;
const long long inf=0x3f3f3f3f3f3f3f3f;
const time_t timeLimit=1.8*CLOCKS_PER_SEC;
int n,a[N+1];
long long res=inf;
long long calc(int per[])
{
	static long long na[N+1],l[N+1],r[N+1];
	for(int i=1;i<=n;++i) {
		na[i]=a[i],l[i]=i-1,r[i]=i+1;
	}
	for(int i=2;i<n;++i) {
		int p=per[i];
		na[l[p]]+=na[p],na[r[p]]+=na[p];
		r[l[p]]=r[p],l[r[p]]=l[p];
	}
	return na[1]+na[n];
}
void solve()
{
	static int per[N+1];
	for(int i=1;i<=n;++i) {
		per[i]=i;
	}
	shuffle(per+2,per+n,default_random_engine(random()));
	long long nres=calc(per);
	for(int t=1;t<=T;++t) {
		int u=rand()%(n-2)+2,v=rand()%(n-2)+2;
		if(u==v) {
			continue;
		}
		swap(per[u],per[v]);
		long long tem=calc(per);
		if(tem<nres) {
			nres=tem;
		} else {
			swap(per[u],per[v]);
		}
	}
	res=min(res,nres);
	return;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
	}
	if(n==2) {
		printf("%d\n",a[1]+a[2]);
		return 0;
	}
	while(clock()<=timeLimit) {
		solve();
	}
	printf("%lld\n",res);
	return 0;
}