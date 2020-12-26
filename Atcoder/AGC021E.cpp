#include<cstdio>
using namespace std;
const int K=5e5,mod=998244353;
int n,k;
int fac[K+1],invf[K+1];
int res;
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
inline int inv(int x)
{
	return pow(x,mod-2);
}
void initFac()
{
	fac[0]=1;
	for(int i=1;i<=k;++i) {
		fac[i]=1ll*fac[i-1]*i%mod;
	}
	invf[k]=inv(fac[k]);
	for(int i=k;i;--i) {
		invf[i-1]=1ll*invf[i]*i%mod;
	}
	return;
}
inline int C(int n,int m)
{
	return (m>=0)&&(m<=n)?1ll*fac[n]*invf[n-m]%mod*invf[m]%mod:0;
}
int main()
{
	scanf("%d%d",&n,&k);
	if(k<n) {
		putchar('0'),putchar('\n');
		return 0;
	}
	initFac();
	for(int r=(k+1)/2;r<=k;++r) {
		if(r==k-r) {
			res=(res+C(k-1,r)-C(k-1,r*2-n+1))%mod;
		} else {
			res=(res+C(k,r)-C(k,r*2-n+1))%mod;
		}
	}
	printf("%d\n",(res+mod)%mod);
	return 0;
}
