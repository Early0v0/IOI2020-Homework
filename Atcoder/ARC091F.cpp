#include<cstdio>
using namespace std;
const int N=200;
int n,a[N+1],k[N+1];
int res;
int SG(int x,int k)
{
	if(x<k) {
		return 0;
	}
	if(x%k==0) {
		return x/k;
	}
	return SG(x-(x-x/k*(k-1))/(x/k+1)*(x/k+1),k);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) {
		scanf("%d%d",&a[i],&k[i]);
	}
	for(int i=1;i<=n;++i) {
		res^=SG(a[i],k[i]);
	}
	puts(res?"Takahashi":"Aoki");
	return 0;
}
