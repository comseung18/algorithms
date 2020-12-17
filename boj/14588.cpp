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

int dist[300][300];
bool isf(const pi& p1, const pi& p2){
    if(p1.first > p2.first) return isf(p2,p1);
    // p1.first <= p2.first
    return p1.second >= p2.first;
}
int main(){
    fastio;
    int N;
    cin >> N;
    const int INF = 987654321;
    rep(i,N) rep(j,N) dist[i][j] = INF;
    rep(i,N) dist[i][i] = 0;
    
    vector<pi> v(N);
    rep(i,N) cin >> v[i].first >> v[i].second;

    rep(i,N) rep(j,N) if(i!=j && isf(v[i],v[j])) dist[i][j] = 1;
    rep(k,N) rep(i,N) rep(j,N){
        if(dist[i][k] + dist[k][j] < dist[i][j]){
            dist[i][j] = dist[i][k] + dist[k][j];
        }
    }
    int Q;
    cin >> Q;
    while(Q--){
        int a,b;
        cin >> a >> b;
        --a; -- b;
        cout << (dist[a][b] == INF? -1 : dist[a][b]) << endl;
    }
    return 0;
}