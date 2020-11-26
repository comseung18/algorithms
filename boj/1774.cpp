#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vector<int>> vvi;

#define endl '\n'
#define rep(i,n) for(int i=0;i<(n);++i)
#define fastio ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);

vi parent(1005);
int u_find(int x){
    if(x == parent[x]) return x;
    return parent[x] = u_find(parent[x]);
}
void u_union(int u, int v){
    u = u_find(u);
    v = u_find(v);
    if(u== v) return;
    parent[v] = u;
}
struct Edge{
    int u,v;
    ll w;
    Edge(int u,int v, ll w)
    :u(u), v(v), w(w) {}
    bool operator<(const Edge& e){
        return w < e.w;
    }
};
int main(){
    //fastio;
    rep(i,1005) parent[i] = i;

    int N,M;
    cin >> N >> M;
    vector<pi> v(N);
    rep(i,N){
        cin >> v[i].first >> v[i].second;
    }

    double ans = 0;
    rep(i,M){
        int u,v;
        cin >>u >> v;
        u_union(u-1,v-1);
    }

    // 간선생성
    vector<Edge> edges;
    rep(i,N) rep(j,N)
        if(i !=j){
            edges.push_back(Edge(i,j,
            (ll)(v[i].first-v[j].first)*
            (ll)(v[i].first-v[j].first) +
            (ll)(v[i].second-v[j].second)*
            (ll)(v[i].second-v[j].second)));
        }

    sort(edges.begin(), edges.end());
    for(const Edge& e : edges){
        if(u_find(e.u) == u_find(e.v)) continue;
        u_union(e.u,e.v);
        ans += sqrt((double)e.w);
    }
    printf("%.2lf",ans);
    return 0;
}