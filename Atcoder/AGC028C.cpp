#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=1e5;
int n,a[N+1],b[N+1];
struct point {
	int id,val;
	bool isA;
};
point p[N*2+1];
int posA[N+1],posB[N+1];
long long sumA,sumB,sumN,res;
int read()
{
	int ret=0;
	char c=getchar();
	while(!isdigit(c)) {
		c=getchar();
	}
	while(isdigit(c)) {
		ret=ret*10+c-'0';
		c=getchar();
	}
	return ret;
}
int main()
{
	n=read();
	for(int i=1;i<=n;++i) {
		a[i]=read(),b[i]=read();
	}
	for(int i=1;i<=n;++i) {
		sumA+=a[i],sumB+=b[i];
		p[i*2-1]=point{i,a[i],true},p[i*2]=point{i,b[i],false};
	}
	sort(p+1,p+n*2+1,[](const point x,const point y) {
		return x.val<y.val;
	});
	for(int i=1;i<=n*2;++i) {
		(p[i].isA?posA:posB)[p[i].id]=i;
	}
	for(int i=1;i<=n;++i) {
		sumN+=p[i].val;
	}
	res=min(sumA,sumB);
	for(int i=1;i<=n;++i) {
		if((posA[i]<=n)&&(posB[i]<=n)) {
			res=min(res,sumN);
			break;
		} else {
			if(posA[i]<=n) {
				res=min(res,sumN+b[i]-p[posA[i]==n?n-1:n].val);
			} else {
				if(posB[i]<=n) {
					res=min(res,sumN+a[i]-p[posB[i]==n?n-1:n].val);
				} else {
					res=min(res,sumN+a[i]+b[i]-p[n-1].val-p[n].val);
				}
			}
		}
	}
	printf("%lld\n",res);
	return 0;
}
