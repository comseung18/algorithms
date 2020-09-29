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

int N,K;
// K >= 5
bool b[26];

vector<string> v;
// b 로 고른 K개 알 수 있다.
int solve(){
    int ret = 0;
    rep(i,N){
        bool tmp = true;
        for(int j=4;j<v[i].size()-4;++j){
            if(!b[(v[i][j]-'a')]){
                tmp = false; break;
            }
        }
        if(tmp) ++ret;
    }
    return ret;
}
// idx 는 현재 추가할 문자의 idx, c 는 지금까지
// 고른 문자의 개수
int ans;
void brute(int idx, int c){
    if(c==K){
        ans = max(ans,solve());
        return;
    }
    for(int i=idx;i<26;++i) if(!b[i]){
        b[i] = true;
        brute(i+1,c+1);
        b[i] = false;
    }
}
int main(){
    fastio;
    cin >> N >> K;
    if(K < 5 ){
        cout << 0; return 0;
    }
    b[('a' - 'a')] = 1;
    b[('n' - 'a')] = 1;
    b[('t' - 'a')] = 1;
    b[('i' - 'a')] = 1;
    b[('c' - 'a')] = 1;

    v = vector<string>(N);
    rep(i,N) cin >> v[i];

    brute(0,5);
    cout << ans;
    return 0;
}