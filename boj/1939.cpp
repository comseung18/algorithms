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

int U,V;
int N,M;
vector<vector<pi>> adj;
vb visited;


// here 에서 w 이상의 간선만 이용하여 dfs
void dfs(int here, int w){
    visited[here] = true;
    if(here == V) return;
    for(auto p : adj[here]){
        int there = p.first;
        int weight = p.second;
        if(!visited[there] && 
        weight >= w){
            dfs(there,w);
        }
    }
}

bool decision(int w){
    visited = vb(N,false);
    // dfs 를 실행
    dfs(U,w);
    return visited[V];
}

int optimise(){
    int hi = 1000000001;
    int lo = 1;
    while(lo+1 < hi){
        int mid = (hi+lo)/2;
        if(decision(mid)){
            lo = mid;
        }
        else{
            hi = mid;
        }
    }
    return lo;
}
int main(){
    fastio;
    cin >> N >> M;
    adj = vector<vector<pi>>(N);
    rep(i,M){
        int a,b,c;
        cin >> a >> b >> c;
        adj[a-1].push_back({b-1,c});
        adj[b-1].push_back({a-1,c});
    }
    cin >> U >> V;
    --U; -- V;
    cout << optimise();
    return 0;
}