#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int q,a,b,fro,to;
int k;
inline int calcA(int p)
{
	return a-p/(k+1)*k-p%(k+1);
}
inline int calcB(int p)
{
	return b-p/(k+1);
}
inline bool check(int p)
{
	return calcB(p)<=1ll*k*calcA(p);
}
int main()
{
	scanf("%d",&q);
	while(q--) {
		scanf("%d%d%d%d",&a,&b,&fro,&to);
		k=max(ceil(1.0*a/(b+1)),ceil(1.0*b/(a+1)));
		int l=0,r=a+b;
		while(l<r) {
			int mid=(l+r)/2;
			if(check(mid)) {
				l=mid+1;
			} else {
				r=mid;
			}
		}
		r=l+calcB(l)-k*calcA(l)+1;
		for(int i=fro;i<=to;++i) {
			if(i<=l) {
				putchar(i%(k+1)?'A':'B');
			} else {
				putchar((i-r)%(k+1)?'B':'A');
			}
		}
		putchar('\n');
	}
	return 0;
}
