#include<cstdio>
#include<algorithm>
#include<bitset>
#include<queue>
using namespace std;
const int N=150,M=150,inf=0x3f3f3f3f;
int n,m;
struct airline {
	int u,v,tim;
};
airline a[M+1];
struct matrix {
	bitset<N>m[N];
};
matrix g;
bitset<N>arr;
int dis[N+1];
int res=inf;
bitset<N>operator *(const bitset<N>x,const matrix y)
{
	bitset<N>ret;
	for(int i=0;i<n;++i) {
		ret[i]=(x&y.m[i]).any();
	}
	return ret;
}
matrix operator *(const matrix x,const matrix y)
{
	matrix ret;
	for(int i=0;i<n;++i) {
		for(int j=0;j<n;++j) {
			if(x.m[i][j]) {
				ret.m[i]|=y.m[j];
			}
		}
	}
	return ret;
}
void pow(matrix x,int times)
{
	while(times) {
		if(times&1) {
			arr=arr*x;
		}
		times>>=1,x=x*x;
	}
	return;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i) {
		scanf("%d%d%d",&a[i].u,&a[i].v,&a[i].tim);
	}
	sort(a+1,a+m+1,[](const airline x,const airline y) {
		return x.tim<y.tim;
	});
	arr[0]=1;
	for(int i=1;i<=m;++i) {
		if(res<=a[i].tim) {
			break;
		}
		pow(g,a[i].tim-a[i-1].tim);
		g.m[a[i].v-1][a[i].u-1]=1;
		static queue<int>que;
		for(int i=1;i<=n;++i) {
			if(arr[i-1]) {
				dis[i]=0,que.push(i);
			} else {
				dis[i]=inf;
			}
		}
		while(!que.empty()) {
			int u=que.front();
			que.pop();
			for(int v=1;v<=n;++v) {
				if(g.m[v-1][u-1]&&(dis[v]==inf)) {
					dis[v]=dis[u]+1,que.push(v);
				}
			}
		}
		res=min(res,a[i].tim+dis[n]);
	}
	if(res==inf) {
		puts("Impossible");
	} else {
		printf("%d\n",res);
	}
	return 0;
}
