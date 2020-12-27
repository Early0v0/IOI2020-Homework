#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;
const int mod=998244353;
string s;
int f(string),g(string);
unordered_map<string,int>mpF,mpG;
int f(string s)
{
	if(mpF.count(s)) {
		return mpF[s];
	}
	int ret=0;
	for(int i=0;i<s.length();++i) {
		ret=(ret+1ll*f(s.substr(0,i))*g(s.substr(i,s.length())))%mod;
	}
	mpF[s]=ret;
	return ret;
}
int g(string s)
{
	static string t;
	if(mpG.count(s)) {
		return mpG[s];
	}
	int ret=0;
	for(int i=1;i<s.length();++i) {
		if(s.length()%i) {
			continue;
		}
		t.assign(i,'1');
		for(int j=0;j<s.length();j+=i) {
			for(int k=0;k<i;++k) {
				if(s[j+k]=='0') {
					t.at(k)='0';
				}
			}
		}
		ret=(ret+f(t))%mod;
	}
	mpG[s]=ret;
	return ret;
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>s;
	mpF[""]=mpG[""]=mpF["0"]=mpG["0"]=1,mpF["1"]=mpG["1"]=2;
	cout<<f(s);
	return 0;
}
