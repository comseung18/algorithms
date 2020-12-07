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
        string s;
        cin >> s;
        int cnt[3] = {0};
        int sum = 0;
        rep(i,s.size()){
            int t = (s[i] - '0')%3;
            ++cnt[t];
            sum += t;
        }
        sum %= 3;
        if(sum == 0) cout << 0 << endl;
        else if(sum == 1){
            if(cnt[1]) cout << ((cnt[1] == 1 && (cnt[2]+cnt[0]) == 0)? -1:1) << endl;
            else if(cnt[2] >= 2) cout << ((cnt[2] == 2 && (cnt[1]+cnt[0]) == 0)? -1:2) << endl;
        }
        else{
            if(cnt[2]) cout << ((cnt[2] == 1 && (cnt[1]+cnt[0]) == 0)? -1:1) << endl;
            else if(cnt[1] >= 2) cout << ((cnt[1] == 2 && (cnt[2]+cnt[0]) == 0)? -1:2) << endl;
        }
         
    }
    return 0;
}