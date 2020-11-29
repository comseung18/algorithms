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

const int dir[5][2]={
    {0,0},{-1,0},{0,-1},{1,0},{0,1}
};
int N;
pi S;
vector<pi> v;
ll dp[2][5];
const ll INF = LONG_LONG_MAX;
inline int d(pi a, pi b){
    // if(a.first < 1 || a.first > 100000) return INF;
    // if(a.second < 1 || a.second > 100000) return INF;
    // if(b.first < 1 || b.first > 100000) return INF;
    // if(a.second < 1 || a.second > 100000) return INF;
    return abs(a.first-b.first) + abs(a.second-b.second);
}
int main(){
    fastio;
    cin >> N;
    cin >> S.first >> S.second;
    v = vector<pi>(N);
    rep(i,N) cin >> v[i].first >> v[i].second;
    
    rep(pos,5){
        pi pn = v[0];
        pn.first += dir[pos][0];
        pn.second += dir[pos][1];
        dp[0][pos] = d(S,pn);
    }
    for(int n=1;n<N;++n){
        rep(pos,5){
            dp[n%2][pos] = INF;
            rep(i,5){
                pi pn = v[n];
                pn.first += dir[pos][0];
                pn.second += dir[pos][1];
                pi pm = v[n-1];
                pm.first += dir[i][0];
                pm.second += dir[i][1];
                int di = d(pn,pm);
                dp[n%2][pos] = min(dp[n%2][pos],dp[(n+1)%2][i] + di);
            }
        }
    }
    ll ans = INF;
    rep(pos,5) ans = min(ans, dp[(N+1)%2][pos]);
    cout << ans;

    return 0;
}