#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=1e5;
int n,m,a[N*2+1];
int pos,res;
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
bool check(int p)
{
	for(int i=p+1,j=n*2;i<j;++i,--j) {
		if(a[i]+a[j]<m) {
			return false;
		}
	}
	return true;
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n*2;++i) {
		a[i]=read();
	}
	sort(a+1,a+n*2+1);
	for(int l=0,r=n;l<r;) {
		int mid=(l+r)/2;
		if(check(mid*2)) {
			pos=mid*2,r=mid;
		} else {
			l=mid+1;
		}
	}
	for(int l=1,r=pos;l<r;++l,--r) {
		res=max(res,a[l]+a[r]);
	}
	for(int l=pos+1,r=n*2;l<r;++l,--r) {
		res=max(res,(a[l]+a[r])%m);
	}
	printf("%d\n",res);
	return 0;
}
