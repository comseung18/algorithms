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

ll N,P,Q,X,Y;
unordered_map<ll,ll> cache;
unordered_map<ll,ll>::iterator it;
ll A(ll i){
  if(i <=0) return 1;
  it = cache.find(i);
  if(it != cache.end()) return it->second;

  ll l = floor(i/P) - X;
  ll r = floor(i/Q) - Y;
  ll ret = A(l)+A(r);
  cache.insert({i, ret});
  return ret;
}
int main(){
    fastio;
    
    cin >> N >> P >> Q >> X >> Y;
    cout << A(N);
    return 0;
}