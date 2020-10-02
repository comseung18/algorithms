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

string a,b;
int cache[4001][4001];
// dp(i,j) : a[i] 랑 b[j] 를 매칭하는 것을 시작으로
// 매칭 시킬 수 있는 최대 값.
// dp(i,j) = if(a[i]==b[j]) dp(i+1,j+1) +1
// else 0
int dp(int i, int j){
    if(i >= a.size() || j >= b.size()) return 0;
    if(a[i] != b[j]) return 0;

    int &ret = cache[i][j];
    if(ret != -1) return ret;

    ret = dp(i+1,j+1) +1;
    return ret;
}
int main(){
    fastio;
    cin >> a >> b;
    memset(cache,-1,sizeof(cache));
    int ans = 0;
    rep(i,a.size()) rep(j,b.size()) ans = max(ans, dp(i,j));
    cout << ans;
    return 0;
}