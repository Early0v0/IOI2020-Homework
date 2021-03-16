#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
const int L=12;
int n,k;
string s,t;
string res;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>k;
	cin>>s;
	t=s,t.resize(n*2),reverse_copy(t.begin(),next(t.begin(),n),next(t.begin(),n));
	string ms=s;
	for(int i=1;i<=n;++i) {
		ms=min(ms,t.substr(i,n));
	}
	int ml=ms.find_first_not_of(ms[0]);
	if(ml==string::npos) {
		ml=ms.size();
	}
	int l=min(n,ml<<min(k-1,L));
	res.append(l,ms[0]);
	res+=ms.substr(ml,n-l);
	cout<<res<<endl;
	return 0;
}
