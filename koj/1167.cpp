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
int n;
vvi adj;
vb visited;
// root 를 root 로 하는 tree 의 높이와 
// root 에서 가장 먼 노드의 번호를 반환.
pi tree_height(int root, int depth=0){
    visited[root] = true;
    pi ret = {root, depth};
    for(int there : adj[root]){
        if(visited[there]) continue;
        pi p = tree_height(there, depth+1);
        if(p.second > ret.second){
            ret.first = p.first;
            ret.second = p.second;
        }
    }
    return ret;
}
int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
        cin >> n;
        adj = vvi(n);
        visited = vb(n,false);
        rep(i,n-1){
            int a,b;
            cin >> a >> b;
            --a; --b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        pi x = tree_height(0,0);
        // 0 에서 가장 먼 친구 : x.first
        visited = vb(n,false);
        cout << tree_height(x.first,0).second << endl;

    }
    return 0;
}