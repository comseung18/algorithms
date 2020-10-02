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



int main(){
    fastio;
    int n;
    cin >> n;
    vi input(n);
    vector<vb> adj(n+1,vb(n+1));
    // adj[i][j] 는 i->j 로 갈 수 있음.
    rep(i,n){
        int t;
        cin >> t;
        input[i] = t;
        adj[i+1][t] = true;
    }
    rep(k,n) rep(i,n) rep(j,n){
        if(adj[i+1][j+1]) continue;
        adj[i+1][j+1] = (adj[i+1][k+1] && adj[k+1][j+1]);
    }
    vector<int> ans;
    rep(i,n){
        if(adj[i+1][input[i]] &&
        adj[input[i]][i+1]){
            ans.push_back(i+1);
        }
    }
    cout << ans.size() << endl;
    rep(i,ans.size()) cout << ans[i] << endl;
    
    return 0;
}