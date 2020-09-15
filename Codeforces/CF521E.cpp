#include<cstdio>
#include<cctype>
#include<vector>
#include<algorithm>
using namespace std;
const int N=2e5;
typedef pair<int,int> pii;
int n,m;
vector<int>e[N+1];
bool vis[N+1],ins[N+1];
int fa[N+1],dep[N+1];
pii p[N+1];
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
int lca(int u,int v)
{
    if(dep[u]>dep[v]) {
        swap(u,v);
    }
    while(dep[v]>dep[u]) {
        v=fa[v];
    }
    while(u!=v) {
        u=fa[u],v=fa[v];
    }
    return u;
}
void link(int *&pos,int u,int v)
{
    while(u!=v) {
        *pos++=u;
        u=fa[u];
    }
    *pos++=v;
    return;
}
void print(int *begin,int *end)
{
    printf("%d",end-begin);
    while(begin!=end) {
        printf(" %d",*begin++);
    }
    putchar('\n');
    return;
}
void solve(int u,int v,int w,int x)
{
    static int path[N+1],*ptr=path;
    if(dep[v]>dep[x]) {
        swap(u,w),swap(v,x);
    }
    int l=lca(u,w);
    puts("YES");
    link(ptr,l,x),reverse(path,ptr);
    print(path,ptr);
    ptr=path;
    link(ptr,x,v),link(ptr,u,l);
    print(path,ptr);
    ptr=path;
    link(ptr,x,x),link(ptr,w,l);
    print(path,ptr);
    exit(0);
}
void dfs(int u,int fat)
{
    fa[u]=fat,dep[u]=dep[fat]+1,vis[u]=ins[u]=true;
    for(int v:e[u]) {
        if(v==fat) {
            continue;
        }
        if(!vis[v]) {
            dfs(v,u);
        } else {
            if(ins[v]) {
                for(int x=u;x!=v;x=fa[x]) {
                    if(p[x].first&&p[x].second) {
                        solve(p[x].first,p[x].second,u,v);
                    } else {
                        p[x]=pii{u,v};
                    }
                }
            }
        }
    }
    ins[u]=false;
    return;
}
int main()
{
    n=read(),m=read();
    for(int i=1,u,v;i<=m;++i) {
        u=read(),v=read();
        e[u].push_back(v),e[v].push_back(u);
    }
    for(int i=1;i<=n;++i) {
        if(!vis[i]) {
            dfs(i,0);
        }
    }
    puts("NO");
    return 0;
}
