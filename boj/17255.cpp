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
string n;
map<string,bool> m;
map<string,bool>::iterator it;

int ans;
void solve(string s,string path){
    m[path] = true;
    if(s==n) {
        ++ans;
        return;
    }
    
    rep(i,10){
        string r = s + (char)('0' +i);
        string l = (char)('0' +i) + s;
        if(n.find(l) != string::npos && !m[l+path]) solve(l,l+path);
        if(n.find(r) != string::npos && !m[r+path]) solve(r, r+path);
    }
}
int main(){
    fastio;
    cin >> n;
    rep(i,10){
        solve(to_string(i),to_string(i));
    }
    cout << ans;
    return 0;
}