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
vi v;
// [L,R] 두개의 블록만 있는 상태에서
// [L.....R] 로 원래의 상태로 역추적을 할 때
// 얻을 수 있는 최대 점수?
int cache[505][505];
int dp(int left, int right){
    // 불변식 left < right
    if(left +1 == right) return 0;
    int &ret = cache[left][right];
    if(ret != -1) return ret;
    ret = 0;
    for(int i=left+1;i<right;++i){
        ret = max(ret, dp(left,i) + dp(i,right) + v[left]*v[i]*v[right]);
    }
    return ret;

}
int main(){
    fastio;
    cin >> n;
    v = vi(n+2);
    v[0] = 1;
    v[n+1] = 1;
    rep(i,n) cin >> v[i+1];
    memset(cache,-1,sizeof(cache));
    cout << dp(0,n+1);
    return 0;
}