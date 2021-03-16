#include<cstdio>
#include<cctype>
#include<limits>
using namespace std;
const int N=1000,Den=100;
int n;
double p[N+1][N+1];
bool vis[N+1];
double f[N+1],prod[N+1];
double res;
void read(int &x)
{
	char c;
	x=0;
	do {
		c=getchar();
	} while(isspace(c));
	do {
		x=x*10+c-'0';
		c=getchar();
	} while(isdigit(c));
	return;
}
int main()
{
	read(n);
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=n;++j) {
			int x;
			read(x);
			p[i][j]=(double)x/Den;
		}
	}
	if(n==1) {
		res=0;
	} else {
		vis[n]=true;
		for(int i=1;i<n;++i) {
			f[i]=1,prod[i]=(1-p[i][n]);
		}
		while(true) {
			int u;
			double minf=numeric_limits<double>::max();
			for(int i=1;i<=n;++i) {
				if(!vis[i]&&(f[i]/(1-prod[i])<minf)) {
					u=i,minf=f[i]/(1-prod[i]);
				}
			}
			vis[u]=true,f[u]/=1-prod[u];
			if(u==1) {
				res=f[1];
				break;
			}
			for(int v=1;v<=n;++v) {
				if(vis[v]) {
					continue;
				}
				f[v]+=f[u]*p[v][u]*prod[v];
				prod[v]*=1-p[v][u];
			}
		}
	}
	printf("%.6lf\n",res);
	return 0;
}
