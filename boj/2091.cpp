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
    int x;
    vi have(4);
    int coin[4] = {1,5,10,25};
    cin >> x;
    rep(i,4) cin >> have[i];

    int cnt[10001] = {0};
    int last = 0; // last 는 전 단계에서 만든 최대 액수
    // last 이후 액수 부터는 자신의 동전을 소모함.

    // cnt[m] 는 m 원을 만드는데 사용하는 동전의 최대 개수
    
    rep(i,4){
        if(have[i] == 0) continue;
        rep(m,10001){
            if(m-coin[i] >= 0){
                if(cnt[m-coin[i]])
                    cnt[m] = max(cnt[m],cnt[m-coin[i]] +1);
                else{
                    if(m%coin[i] == 0)
                        cnt[m] = max(cnt[m],m/coin[i]);
                }
                if(last < m && ((m-last)/coin[i] >= have[i])){
                    last = m;
                    break;
                }
            }
        }
    }
    
    if(cnt[x] == 0){
        cout << "0 0 0 0";
        return 0;
    }
    if(cnt[x] == x){
        cout << x << " 0 0 0";
        return 0;
    }
    rep(B,have[1]+1)
        rep(C,have[2]+1){
            // 24*D = x-cnt[x] - 4*B - 9*C
            if((x-cnt[x] - 4*B - 9*C)%24) continue;
            int D = (x-cnt[x] - 4*B - 9*C)/24;
            if(D < 0 || D > have[3]) continue;
            int A = cnt[x]-B-C-D;
            if(A<0 || A>have[0]) continue;
            cout << A << ' ' << B << ' ' << C << ' ' << D;
            return 0;
        }
    cout << "좆망";
    return 0;
}