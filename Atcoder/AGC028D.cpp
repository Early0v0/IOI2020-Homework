#include<cstdio>
using namespace std;
const int N=300,mod=1e9+7;
int n,k;
int link[N*2+1];
int sum[N*2+1];
int f[N*2+1][N*2+1],g[N*2+1];
int res;
int calc(int l,int r)
{
	if(sum[r]-sum[l-1]&1) {
		return 0;
	}
	for(int i=l;i<=r;++i) {
		if(link[i]&&((link[i]<l)||(link[i]>r))) {
			return 0;
		}
	}
	f[l][r]=g[sum[r]-sum[l-1]];
	for(int i=l+1;i<r;++i) {
		f[l][r]=(f[l][r]-1ll*f[l][i]*g[sum[r]-sum[i]])%mod;
	}
	return 1ll*f[l][r]*g[(n-k)*2-(sum[r]-sum[l-1])]%mod;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1,u,v;i<=k;++i) {
		scanf("%d%d",&u,&v);
		link[u]=v,link[v]=u;
	}
	for(int i=1;i<=n*2;++i) {
		sum[i]=sum[i-1]+(link[i]?0:1);
	}
	g[0]=1;
	for(int i=2;i<=n*2;i+=2) {
		g[i]=1ll*g[i-2]*(i-1)%mod;
	}
	for(int i=1;i<n*2;++i) {
		for(int j=i+1;j<=n*2;j+=2) {
			res=(res+calc(i,j))%mod;
		}
	}
	printf("%d\n",(res+mod)%mod);
	return 0;
}
