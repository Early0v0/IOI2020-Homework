#include<iostream>
#include<algorithm>
using namespace std;
const int N=5000;
const long long inf=0x3f3f3f3f3f3f3f3f;
int n,a,b;
int p[N+2];
int c[N+2][N+2];
long long f[N+2];
int main()
{
	cin>>n>>a>>b;
	for(int i=1;i<=n;++i) {
		cin>>p[i];
	}
	p[0]=0,p[n+1]=n+1;
	for(int i=0;i<=n+1;++i) {
		if(i>0) {
			copy_n(c[i-1],n+2,c[i]);
		}
		for(int j=p[i];j<=n+1;++j) {
			++c[i][j];
		}
	}
	f[0]=0;
	for(int i=1;i<=n+1;++i) {
		f[i]=inf;
		for(int j=i-1,v=-1;j>=0;--j) {
			if((p[j]>p[i])||(p[j]<v)) {
				continue;
			}
			v=p[j];
			f[i]=min(f[i],f[j]+1ll*a*((c[i-1][n+1]-c[i-1][p[i]])-(c[j][n+1]-c[j][p[i]]))+1ll*b*(c[i-1][p[j]]-c[j][p[j]]));
		}
	}
	cout<<f[n+1]<<endl;
	return 0;
}
