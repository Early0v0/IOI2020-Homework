#include<cstdio>
#include<algorithm>
#define For(i,l,r) for(int i=l;i<r;++i)
using namespace std;
const int N=500;
int n,k;
int r[N][N];
int main()
{
	scanf("%d",&k);
	n=min(k,N);
	For(i,0,n) {
		For(j,0,n) {
			r[i][j]=(i+j)%n+1;
		}
	}
	if(k!=n) {
		For(i,n,k) {
			For(j,0,n) {
				if((i-j)%2==0) {
					r[(i-j)%n][j]=i+1;
				}
			}
		}
	}
	printf("%d\n",n);
	For(i,0,n) {
		For(j,0,n) {
			printf("%d ",r[i][j]);
		}
		putchar('\n');
	}
	return 0;
}
