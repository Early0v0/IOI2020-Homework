#include<iostream>
using namespace std;
const int N=3000,M=3000,mod=1e9+7,inv2=(mod+1)/2;
int n,m;
int a[N+1];
pair<int,int> w[M+1];
int f[N+1][N+1];
int res;
int pow(int x,int t)
{
	int r=1;
	do {
		(t%2)&&(r=1ll*r*x%mod);
	} while(x=1ll*x*x%mod,t/=2);
	return r;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;++i) {
		cin>>a[i];
	}
	for(int i=1;i<=m;++i) {
		cin>>w[i].first>>w[i].second;
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n;++j) {
			f[i][j]=a[i]<a[j];
		}
	}
	for(int i=1;i<=m;++i) {
		auto [x,y]=w[i];
		f[x][y]=f[y][x]=1ll*(f[x][y]+f[y][x])*inv2%mod;
		for(int j=1;j<=n;++j) {
			if((j==x)||(j==y)) {
				continue;
			}
			f[j][x]=f[j][y]=1ll*(f[j][x]+f[j][y])*inv2%mod,
			f[x][j]=f[y][j]=1ll*(f[x][j]+f[y][j])*inv2%mod;
		}
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<i;++j) {
			res=(res+f[i][j])%mod;
		}
	}
	res=1ll*res*pow(2,m)%mod;
	cout<<res<<endl;
	return 0;
}
