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
    string s;
    getline(cin,s);
    while(T--){
        getline(cin,s);
        int cnt[26]={0};
        int index[26];
        rep(i,26) index[i] = -1;

        for(int i=0;i<s.size();i++){
            if(!isalpha(s[i])) break;
            cnt[s[i]-'a'] += 1;
            if(index[s[i]-'a'] == -1) index[s[i]-'a'] = i;
        }
        int idx = -1;
        rep(i,26) if(cnt[i] == 1){
            if(idx == -1) idx = index[i];
            else idx = min(idx, index[i]);
        }
        cout << idx << endl;
    }
    return 0;
}