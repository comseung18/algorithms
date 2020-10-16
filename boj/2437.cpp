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
    vi v(n);
    rep(i,n) cin >> v[i];
    sort(v.begin(),v.end());
    if(v[0] != 1){
        cout << 1; return 0;
    }
    int s = 1;
    for(int i=1;i<n;++i){
        if(s+1 < v[i]){
            cout << s+1; return 0;
        }
        s += v[i];
    }
    cout << s+1;
    return 0;
}