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

vi v[4];
map<int,int> ab;
int main(){
    fastio;
    int n;
    cin >> n;
    
    rep(i,4) v[i] = vi(n);
    rep(i,n){
        rep(j,4) cin >> v[j][i];
    }
    
   
    rep(i,n){
        rep(j,n){
            int a = v[0][i] + v[1][j];
            ab[a] += 1;
        }
    }

    ll s = 0;
    rep(i,n){
        rep(j,n){
            int t = v[2][i] + v[3][j];
            auto it = ab.find(-t);
            if(it != ab.end()) s += it->second;
        }
    }
    cout << s;
    return 0;
}