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
    int N,K;
    cin >> N >> K;
    vi v(N);
    rep(i,N){
        cin >> v[i];
        if(i>0) v[i] += v[i-1];
    }
    // 부분합의 개수를 저장
    unordered_map<int,int> m;
    unordered_map<int,int>::iterator it;
    ll ans = 0;
    rep(i,N){
        
        it = m.find(K-v[i]);
        if(it != m.end()){
            ans += it->second;
        }
        m[-v[i]]++;
        if(v[i] == K) ++ans;
    }
    cout << ans;
    return 0;
}