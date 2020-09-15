#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int N=3e5;
int n,a[N+1];
struct tree {
    int minn,tag,cnt;
};
tree t[N*4];
int pos[N+1],tmax,stkmax[N+1],tmin,stkmin[N+1];
long long res;
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
#define lson num<<1
#define rson num<<1|1
void build(int num,int l,int r)
{
    t[num].cnt=r-l+1;
    if(l==r) {
        return;
    }
    int mid=(l+r)/2;
    build(lson,l,mid),build(rson,mid+1,r);
    return;
}
void push_up(int num)
{
    t[num].minn=min(t[lson].minn,t[rson].minn);
    t[num].cnt=(t[num].minn==t[lson].minn?t[lson].cnt:0)+(t[num].minn==t[rson].minn?t[rson].cnt:0);
    return;
}
void push_down(int num)
{
    if(!t[num].tag) {
        return;
    }
    t[lson].minn+=t[num].tag,t[lson].tag+=t[num].tag;
    t[rson].minn+=t[num].tag,t[rson].tag+=t[num].tag;
    t[num].tag=0;
    return;
}
void modify(int num,int l,int r,int fro,int to,int val)
{
    if((fro<=l)&&(to>=r)) {
        t[num].minn+=val,t[num].tag+=val;
        return;
    }
    push_down(num);
    int mid=(l+r)/2;
    if(fro<=mid) {
        modify(lson,l,mid,fro,to,val);
    }
    if(to>mid) {
        modify(rson,mid+1,r,fro,to,val);
    }
    push_up(num);
    return;
}
#undef lson
#undef rson
int main()
{
    n=read();
    for(int i=1,x,y;i<=n;++i) {
        x=read(),y=read();
        a[x]=y;
    }
    build(1,1,n);
    for(int i=1;i<=n;++i) {
        while(tmax&&(a[stkmax[tmax]]<a[i])) {
            modify(1,1,n,stkmax[tmax-1]+1,stkmax[tmax],-a[stkmax[tmax]]);
            --tmax;
        }
        while(tmin&&(a[stkmin[tmin]]>a[i])) {
            modify(1,1,n,stkmin[tmin-1]+1,stkmin[tmin],a[stkmin[tmin]]);
            --tmin;
        }
        modify(1,1,n,pos[a[i]]+1,i,-1);
        modify(1,1,n,stkmax[tmax]+1,i,a[i]),modify(1,1,n,stkmin[tmin]+1,i,-a[i]);
        pos[a[i]]=i,stkmax[++tmax]=stkmin[++tmin]=i;
        res+=t[1].cnt;
    }
    printf("%I64d\n",res);
    return 0;
}
