#include<cstdio>
#include<cctype>
#include<vector>
#include<queue>
#include<ccomplex>
#include<cmath>
#include<numeric>
using namespace std;
typedef pair<int,int> pii;
typedef complex<double> com;
const int N=50,M=100,T=20000,L=1<<16,Den=1e5,inf=0x3f3f3f3f;
int n,m,t,x;
struct edge {
	int u,v,w;
	int p[T+1];
	double q[T];
}e[M+1];
vector<pii> rg[N+1];
int dis[N+1];
int rev[L];
com uni[L],iuni[L];
double f[N+1][T+1],g[M+1][T+1];
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
void spfa()
{
	static queue<int> q;
	static bool inq[N+1];
	q.push(n),inq[n]=true;
	fill(dis+1,dis+n,inf);
	while(!q.empty()) {
		int u=q.front();
		q.pop(),inq[u]=false;
		for(pii re:rg[u]) {
			int v=re.first,w=re.second;
			if(dis[v]<=dis[u]+w) {
				continue;
			}
			dis[v]=dis[u]+w;
			if(!inq[v]) {
				q.push(v),inq[v]=true;
			}
		}
	}
	return;
}
void initRev(int n)
{
	for(int i=0;i<n;++i) {
		rev[i]=rev[i>>1]>>1|(i&1?n>>1:0);
	}
	return;
}
void initUni(int n)
{
	const double Pi=acos(-1);
	for(int i=2;i<=n;i<<=1) {
		uni[i]=com{cos(Pi*2/i),sin(Pi*2/i)};
		iuni[i]=com{cos(Pi*2/i),-sin(Pi*2/i)};
	}
	return;
}
void fft(com f[],int n,bool flag)
{
	for(int i=0;i<n;++i) {
		if(i<rev[i]) {
			swap(f[i],f[rev[i]]);
		}
	}
	for(int i=2,l=1;i<=n;i<<=1,l<<=1) {
		com u=flag?uni[i]:iuni[i];
		for(int j=0;j<n;j+=i) {
			com w(1,0);
			for(int k=j;k<j+l;++k) {
				com tem=w*f[l+k];
				f[l+k]=f[k]-tem,f[k]+=tem;
				w*=u;
			}
		}
	}
	if(!flag) {
		for(int i=0;i<n;++i) {
			f[i]/=n;
		}
	}
	return;
}
void cdq(int l,int r)
{
	static com polyF[L],polyG[L];
	if(l==r) {
		for(int i=1;i<=m;++i) {
			f[e[i].u][l]=min(f[e[i].u][l],e[i].w+g[i][l]);
		}
		return;
	}
	int mid=(l+r)/2;
	cdq(mid+1,r);
	int len=1;
	while(len<=r-l) {
		len<<=1;
	}
	initRev(len);
	for(int i=1;i<=m;++i) {
		for(int j=mid;j<r;++j) {
			polyF[j-mid]=com{f[e[i].v][j+1],0};
		}
		fill(polyF+r-mid,polyF+len,com{0,0});
		for(int j=l;j<r;++j) {
			polyG[j-l]=com{e[i].q[j+t-r],0};
		}
		fill(polyG+r-l,polyG+len,com{0,0});
		fft(polyF,len,true),fft(polyG,len,true);
		for(int j=0;j<len;++j) {
			polyF[j]*=polyG[j];
		}
		fft(polyF,len,false);
		for(int j=l;j<=mid;++j) {
			g[i][j]+=polyF[j+r-l-mid-1].real();
		}
	}
	cdq(l,mid);
	return;
}
int main()
{
	read(n),read(m),read(t),read(x);
	for(int i=1;i<=m;++i) {
		read(e[i].u),read(e[i].v),read(e[i].w);
		rg[e[i].v].push_back(pii{e[i].u,e[i].w});
		for(int j=1;j<=t;++j) {
			read(e[i].p[j]);
			e[i].q[t-j]=(double)e[i].p[j]/Den;
		}
	}
	spfa();
	for(int i=1;i<n;++i) {
		fill(f[i],f[i]+t+1,inf);
	}
	for(int i=1;i<=m;++i) {
		for(int j=1;j<=t;++j) {
			g[i][j]=e[i].q[j-1]*(dis[e[i].v]+x);
		}
		partial_sum(g[i],g[i]+t+1,g[i]);
	}
	initUni(t<<1);
	cdq(0,t);
	printf("%.6lf\n",f[1][0]);
	return 0;
}
