#include<iostream>
using namespace std;
int n;
int main()
{
	ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n;
	if(__builtin_popcount(n)>1) {
		cout<<"Yes"<<endl;
		for(int i=2;i<n;i+=2) {
			cout<<1<<' '<<i<<'\n';
			cout<<i<<' '<<i+1<<'\n';
			cout<<1<<' '<<i+n+1<<'\n';
			cout<<i+n+1<<' '<<i+n<<'\n';
		}
		if(n%2==0) {
			int lb=n&-n;
			cout<<lb<<' '<<n<<'\n';
			cout<<n+(n^lb)+1<<' '<<n*2<<'\n';
		}
		cout<<3<<' '<<n+1<<'\n';
	} else {
		cout<<"No"<<endl;
	}
	return 0;
}
