#include<cstdio>
#include<cctype>
#include<stack>
#define fir first
#define sec second
using namespace std;
const int N=2e5;
typedef pair<int,int> pii;
int n,a[N+1];
int res;
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
void insert(stack<pii>*s,int v,int x)
{
	while(s->top().fir>v) {
		s->pop();
	}
	if(s->top().fir==v) {
		++s->top().sec;
	} else {
		s->push(pii{v,1});
	}
	if((s->size()>1)&&(s->top().sec==x)) {
		s->pop();
		insert(s,v-1,x);
	}
	return;
}
bool check(int x)
{
	static stack<pii>s;
	if(x==1) {
		for(int i=1;i<n;++i) {
			if(a[i]>a[i+1]) {
				return false;
			}
		}
		return true;
	}
	while(!s.empty()) {
		s.pop();
	}
	s.push(pii{0,0});
	for(int i=2;i<=n;++i) {
		if(a[i]<=a[i-1]) {
			insert(&s,a[i],x);
		}
	}
	for(int t=s.size()-1;t;--t) {
		s.pop();
	}
	return !s.top().sec;
}
int main()
{
	n=read();
	for(int i=1;i<=n;++i) {
		a[i]=read();
	}
	for(int l=1,r=n;l<=r;) {
		int mid=(l+r)/2;
		if(check(mid)) {
			r=mid-1,res=mid;
		} else {
			l=mid+1;
		}
	}
	printf("%d\n",res);
	return 0;
}
