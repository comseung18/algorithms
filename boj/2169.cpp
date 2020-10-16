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

const int INF = INT_MAX;
const int NOT_VISIT = INT_MAX;

int N,M;
int v[1001][1001];

int cache[1001][1001][2][2];
 
int dp(int y, int x, bool left, bool right){
    if(y <0 || x < 0 || y >= N || x >= M) return -INF;

    
    int &ret = cache[y][x][left][right];
    if(ret != NOT_VISIT) return ret;

    ret = v[y][x];
    if(y == N-1 && x == M-1) return ret;

    int best = -INF;
    if(left) best = max(best, dp(y,x-1,true,false));
    if(right) best = max(best, dp(y,x+1,false,true));
    best = max(best, dp(y+1,x,true,true));

    // 경로가 없다면,
    if(best == -INF){
        ret = -INF;
        return ret;
    }


    ret = best + ret;
    return ret;
}
int main(){
    fastio;
    rep(i,1001) rep(j,1001) rep(k,2) rep(m,2)
        cache[i][j][k][m] = NOT_VISIT;
    
    cin >> N >> M;
    rep(i,N) rep(j,M) cin >> v[i][j];

    cout << dp(0,0,true,true);
    return 0;
}