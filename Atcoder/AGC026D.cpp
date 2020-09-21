#include<cstdio>
using namespace std;
const int N=100,mod=1e9+7;
int n,h[N+1];
int f[N+1][N+1];
int pow(int x,int times)
{
	int ret=1;
	while(times) {
		if(times&1) {
			ret=1ll*ret*x%mod;
		}
		times>>=1,x=1ll*x*x%mod;
	}
	return ret;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) {
		scanf("%d",&h[i]);
	}
	h[0]=1,f[0][0]=1;
	for(int i=1;i<=n;++i) {
		for(int j=0;j<=n;++j) {
			if(h[j]>h[i]) {
				continue;
			}
			if(h[j]<h[i-1]) {
				if(h[i]<h[i-1]) {
					f[i][j]=(f[i-1][j]+f[i-1][i])%mod;
				} else {
					f[i][j]=1ll*(f[i-1][j]+f[i-1][i-1])*pow(2,h[i]-h[i-1])%mod;
				}
			} else {
				f[i][j]=2ll*f[i-1][i-1]*pow(2,h[i]-h[j])%mod;
			}
		}
	}
	printf("%d\n",f[n][0]);
	return 0;
}
