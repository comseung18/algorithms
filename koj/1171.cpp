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
    int T;
    cin >> T;
    while(T--){
        int C;
        cin >> C;
        vi a = vi(C);
        vi b = vi(C);
        rep(i,C) cin >> a[i];
        rep(i,C) cin >> b[i];
        int ans_idx = 0;
        ll s = 0; // 총 합
        ll fuel = 0; // <-- 현재 가진 연료량
        rep(i,C){
            fuel += a[i] - b[i];
            if(fuel < 0){
                ans_idx = i+1;
                s += fuel;
                fuel = 0;
            }
        }
        if((s + fuel) >= 0){
            cout << ans_idx << endl;
        }
        else cout << -1 << endl;
    }
    return 0;
}