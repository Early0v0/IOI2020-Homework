#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=1e5;
int n,s,pos[N+1];
long long arr[N+1];
template<class T>T read()
{
	T ret=0;
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
long long solve(int fro,int to,int end)
{
	if(s<=pos[fro]) {
		return pos[to]-s;
	}
	if(s>=pos[to]) {
		return s-pos[fro];
	}
	if(arr[fro]>=arr[to]) {
		arr[fro]+=arr[to];
		return solve(fro,to-1,fro)+(end==to?pos[to]-pos[fro]:0);
	} else {
		arr[to]+=arr[fro];
		return solve(fro+1,to,to)+(end==fro?pos[to]-pos[fro]:0);
	}
}
int main()
{
	n=read<int>(),s=read<int>();
	for(int i=1;i<=n;++i) {
		pos[i]=read<int>(),arr[i]=read<long long>();
	}
	printf("%lld\n",solve(1,n,arr[1]<arr[n]?1:n));
	return 0;
}
