#include<cstdio>
using namespace std;
const int N=1500,K=1e5,mod=1e9+7;
int n,m,a,b,k,p;
long long fac[K+1],inv[K+1],c[N+1],sc[N+1],f[N+1][N+1],s[N+1][N+1],ss[N+1];
long long pow(long long x,int times)
{
	long long res=1;
	for(;times;x=x*x%mod,times>>=1) {
		if(times&1) {
			res=res*x%mod;
		}
	}
	return res;
}
void init()
{
	fac[0]=1;
	for(int i=1;i<=k;++i) {
		fac[i]=fac[i-1]*i%mod;
	}
	inv[k]=pow(fac[k],mod-2);
	for(int i=k;i;--i) {
		inv[i-1]=inv[i]*i%mod;
	}
	return;
}
inline long long C(int n,int m)
{
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int main()
{
	scanf("%d%d%d%d%d",&n,&m,&a,&b,&k);
	p=a*pow(b,mod-2)%mod;
	init();
	for(int i=0;(i<=m)&&(i<=k);++i) {
		c[i]=C(k,i)*pow(p,i)%mod*pow(1-p,k-i)%mod;
	}
	sc[0]=c[0];
	f[0][m]=s[0][m]=1;
	for(int i=1;i<m;++i) {
		sc[i]=(sc[i-1]+c[i])%mod;
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			ss[j]=(ss[j-1]+(s[i-1][m]-s[i-1][j-1])*c[j-1])%mod;
			f[i][j]=(ss[j]-s[i-1][m-j]*sc[j-1])%mod*c[m-j]%mod;
			s[i][j]=(s[i][j-1]+f[i][j])%mod;
		}
	}
	printf("%lld\n",(s[n][m]+mod)%mod);
	return 0;
}
