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
ll f(ll n, int p, int k){
    return (ll)floor(n/(ll)k)*k*9ll + (floor(n/3ll)*3)*k;
}
int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
        int P,K;
        cin >> P >> K;
        ll s = 3ll*(ll)K*(ll)P;
        for(int i=0;i<101;i++){
            ll n = s/(9ll + (ll)K) + (ll)i;
            if(s== f(n,P,K)){
                cout << n << endl;
                goto here;
            }
        }
        cout  << -1 << endl;
        here:;
    }
    return 0;
}