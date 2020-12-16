#include<cstdio>
#include<cctype>
#define For(i,l,r) for(int i=l;i<=r;++i)
using namespace std;
const int N=185;
int n,m;
int a[N+1][N+1];
int s[N+1][N+1];
int f[2][N+1][N+1][N+1],g[2][N+1][N+1][N+1];
int res;
bool nullComplexity(int u,int d,int l,int r)
{
	int t=s[d][r]-s[d][l-1]-s[u-1][r]+s[u-1][l-1];
	return !t||(t==(d-u+1)*(r-l+1));
}
bool checkComplexity(int u,int d,int l,int r)
{
	int o=res&1^1;
	if(int nexu=f[o][u][l][r]+1) {
		if((nexu>d)||(f[o][nexu][l][r]>=d)) {
			return true;
		}
	}
	if(int nexl=g[o][l][u][d]+1) {
		if((nexl>r)||(g[o][nexl][u][d]>=r)) {
			return true;
		}
	}
	return false;
}
int main()
{
	scanf("%d%d",&n,&m);
	For(i,1,n) {
		For(j,1,m) {
			char c=getchar();
			while(isspace(c)) {
				c=getchar();
			}
			a[i][j]=c=='#';
		}
	}
	For(i,1,n) {
		For(j,1,m) {
			s[i][j]=s[i][j-1]+s[i-1][j]-s[i-1][j-1]+a[i][j];
		}
	}
	if(!nullComplexity(1,n,1,m)) {
		For(u,1,n) {
			For(l,1,m) {
				For(r,l,m) {
					if(nullComplexity(u,u,l,r)) {
						int dl=u,dr=n;
						while(dl<dr) {
							int dmid=(dl+dr+1)/2;
							if(nullComplexity(u,dmid,l,r)) {
								dl=dmid;
							} else {
								dr=dmid-1;
							}
						}
						f[0][u][l][r]=dl;
					} else {
						f[0][u][l][r]=-1;
					}
				}
			}
		}
		For(l,1,m) {
			For(u,1,n) {
				For(d,u,n) {
					if(nullComplexity(u,d,l,l)) {
						int rl=l,rr=m;
						while(rl<rr) {
							int rmid=(rl+rr+1)/2;
							if(nullComplexity(u,d,l,rmid)) {
								rl=rmid;
							} else {
								rr=rmid-1;
							}
						}
						g[0][l][u][d]=rl;
					} else {
						g[0][l][u][d]=-1;
					}
				}
			}
		}
		do {
			++res;
			For(u,1,n) {
				For(l,1,m) {
					For(r,l,m) {
						if(checkComplexity(u,u,l,r)) {
							int dl=u,dr=n;
							while(dl<dr) {
								int dmid=(dl+dr+1)/2;
								if(checkComplexity(u,dmid,l,r)) {
									dl=dmid;
								} else {
									dr=dmid-1;
								}
							}
							f[res&1][u][l][r]=dl;
						} else {
							f[res&1][u][l][r]=-1;
						}
					}
				}
			}
			For(l,1,m) {
				For(u,1,n) {
					For(d,u,n) {
						if(checkComplexity(u,d,l,l)) {
							int rl=l,rr=m;
							while(rl<rr) {
								int rmid=(rl+rr+1)/2;
								if(checkComplexity(u,d,l,rmid)) {
									rl=rmid;
								} else {
									rr=rmid-1;
								}
							}
							g[res&1][l][u][d]=rl;
						} else {
							g[res&1][l][u][d]=-1;
						}
					}
				}
			}
		} while(f[res&1][1][1][m]!=n);
	}
	printf("%d\n",res);
	return 0;
}
