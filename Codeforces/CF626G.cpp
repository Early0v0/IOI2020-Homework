#include<cstdio>
#include<cctype>
#include<set>
#include<cfloat>
using namespace std;
const int N=2e5;
int n,t,q,p[N+1],l[N+1];
int c[N+1];
struct raffle {
	int id,num;
	double val;
	raffle(int Id,int Num): id(Id),num(Num)
	{
		if(num<0) {
			val=DBL_MAX;
			return;
		}
		if(num>=l[id]) {
			val=0;
			return;
		}
		val=(double)p[id]*l[id]/(num+l[id]+1)/(num+l[id]);
		return;
	}
};
inline bool operator <(const raffle x,const raffle y)
{
	return x.val!=y.val?x.val<y.val:x.id<y.id;
}
multiset<raffle> s,e;
double res;
void read(int &x)
{
	char c;
	x=0;
	do {
		c=getchar();
	} while(isspace(c));
	do {
		x=x*10+c-'0';
		c=getchar();
	} while(isdigit(c));
	return;
}
void insert()
{
	raffle x=*s.rbegin();
	++c[x.id];
	s.erase(x),s.insert(raffle(x.id,x.num+1));
	e.erase(raffle(x.id,x.num-1)),e.insert(x);
	res+=x.val;
	return;
}
void remove()
{
	raffle x=*e.begin();
	--c[x.id];
	e.erase(x),e.insert(raffle(x.id,x.num-1));
	s.erase(raffle(x.id,x.num+1)),s.insert(x);
	res-=x.val;
	return;
}
int main()
{
	read(n),read(t),read(q);
	for(int i=1;i<=n;++i) {
		read(p[i]);
	}
	for(int i=1;i<=n;++i) {
		read(l[i]);
	}
	for(int i=1;i<=n;++i) {
		s.insert(raffle(i,0)),e.insert(raffle(i,-1));
	}
	while(t--) {
		insert();
	}
	while(q--) {
		int opt,x;
		read(opt),read(x);
		s.erase(raffle(x,c[x])),e.erase(raffle(x,c[x]-1));
		res-=(double)p[x]*min(l[x],c[x])/(min(l[x],c[x])+l[x]);
		l[x]+=opt==1?1:-1;
		s.insert(raffle(x,c[x])),e.insert(raffle(x,c[x]-1));
		res+=(double)p[x]*min(l[x],c[x])/(min(l[x],c[x])+l[x]);
		if(s.rbegin()->val>e.begin()->val) {
			remove(),insert();
		}
		printf("%.6lf\n",res);
	}
	return 0;
}
