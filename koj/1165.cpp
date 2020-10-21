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
int P,Q,R; // 산봉우리의 수, 등산로의 수, 산장의 수
vector<vector<pi>> adj;
vi dist;
vb visited;
const int INF = 987654321;
int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
        cin >> P >> Q >> R;
        adj = vector<vector<pi>>(P+1);
        rep(i,Q){
            int a,b,c;
            cin >> a >> b >> c;
            --a; --b;
            adj[b].push_back({-c,a});
        }
        rep(i,R){
            int t;
            cin >> t;
            --t;
            adj[P].push_back({0,t});
        }
        // P 로 부터 다익스트라 시작
        dist = vi(P,INF); // P번 노드에서 각 노드 사이의 거리
        visited = vb(P,false);
        priority_queue<pi> q;
        for(pi p : adj[P]){
            int there = p.second;
            q.push({0,there});
        }

        while(!q.empty()){
            pi p = q.top();
            q.pop();

            int here = p.second;
            int here_dist = -p.first;

            if(visited[here]) continue;

            dist[here] = here_dist;
            visited[here] = true;

            for(pi t : adj[here]){
                int there = t.second;
                int there_dist = -t.first;
                q.push({-(there_dist+here_dist),there});
            }
        }
        // 가장 큰 dist 값 출력
        int ans_idx = 0;
        int ans_dist = 0;
        rep(i,P){
            if(dist[i] > ans_dist){
                ans_dist = dist[i];
                ans_idx = i;
            }
        }
        cout << ans_idx+1 << ' ' << ans_dist << endl;


    }
    return 0;
}