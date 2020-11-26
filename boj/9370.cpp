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

const int INF = 987654321;

void getDist(int s, vi& dist, const vector<vector<pi> >& adj){
    int n = adj.size();
    dist = vi(n,INF);
    priority_queue< pi, vector<pi>, greater<pi> > pq;
    pq.push({0,s});
    while(!pq.empty()){
        pi top = pq.top();
        pq.pop();
        if(dist[top.second] <= top.first) continue;

        // dist[top.second] > top.first
        dist[top.second] = top.first;
        for(pi p : adj[top.second]){
            pq.push({p.first + top.first ,p.second});
        }
    }
    return;
}
int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
        int n,m,t;
        // 교차로, 도로, 목적지 후보의 개수
        cin >>n >>m >> t;
        int s,g,h;
        int gh = INF;
        cin >> s >> g >> h;
        // s 는 출발지, g h 는 g 와 h 사이에 있는 도로를 지나갔다는 뜻
        vector<vector<pi>> adj(n+1);
        rep(i,m){
            int u,v,w;
            cin >> u >> v >> w;
            adj[u].push_back({w,v});
            adj[v].push_back({w,u});
            if((u == g && v == h) || (u ==h && v == g)){
                gh = w;
            }
        }
        vi dist_s,dist_g,dist_h;
        getDist(s,dist_s,adj);
        getDist(g,dist_g,adj);
        getDist(h,dist_h,adj);
        vi ans;
        rep(i,t){
            int x;
            cin >> x;
            if((dist_s[g] + gh + dist_h[x] == dist_s[x])
            ||(dist_s[h] + gh + dist_g[x] == dist_s[x]))
                ans.push_back(x);
        }
        sort(ans.begin(),ans.end());
        rep(i,ans.size()) cout << ans[i] << ' ';
        cout << endl;
    }
    return 0;
}