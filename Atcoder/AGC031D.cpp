#include<cstdio>
#include<cctype>
#include<array>
#include<algorithm>
#define For(i,l,r) for(int i=l;i<=r;++i)
using namespace std;
const int N=1e5;
typedef array<int,N+1> arr;
int n,k;
arr id;
arr a[7];
arr res;
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
arr operator*(const arr x,const arr y)
{
	arr ret;
	For(i,1,n) {
		ret[i]=x[y[i]];
	}
	return ret;
}
arr inv(const arr x)
{
	arr ret;
	For(i,1,n) {
		ret[x[i]]=i;
	}
	return ret;
}
arr pow(arr x,int times)
{
	arr ret=id;
	while(times) {
		if(times&1) {
			ret=ret*x;
		}
		times>>=1,x=x*x;
	}
	return ret;
}
int main()
{
	n=read(),k=read();
	For(i,1,n) {
		id[i]=i;
	}
	a[0]=id;
	For(i,1,n) {
		a[1][i]=read();
	}
	For(i,1,n) {
		a[2][i]=read();
	}
	For(i,3,6) {
		a[i]=a[i-1]*inv(a[i-2]);
	}
	if(k%6==0) {
		res=pow(a[2]*inv(a[1])*inv(a[2])*a[1],k/6-1)*a[6]*pow(inv(a[1])*a[2]*a[1]*inv(a[2]),k/6-1);
	} else {
		res=pow(a[2]*inv(a[1])*inv(a[2])*a[1],k/6)*a[k%6]*pow(inv(a[1])*a[2]*a[1]*inv(a[2]),k/6);
	}
	for_each(res.begin()+1,res.begin()+n+1,[](int x)->void {
		printf("%d ",x);
	});
	putchar('\n');
	return 0;
}
