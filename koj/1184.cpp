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
    vi v(n+1);
    rep(i,n) cin >> v[i+1];
    int m;
    cin >> m;
    vi t(n+1,0);
    set<int> s;
    while(m--){
        char q;
        int k,x;
        cin >> q;
        if(q== 'F'){
            cin >> k >> x;
            auto sit = s.lower_bound(-k);
            if(sit != s.end() && t[-(*sit)] >= x) continue;

            sit = s.find(-k);
            if(sit == s.end()) s.insert(-k);

            t[k] = max(t[k],x);
            
            auto it = s.begin();
            sit = s.find(-k);
            while(it != s.end() && it != sit){
                if(t[-(*it)] <= t[k]) it = s.erase(it);
                else break;
            }
        }else{
            cin >> k;
            auto it = s.lower_bound(-k);
            if(it == s.end()) cout << v[k] << endl;
            else cout << max(t[-(*it)],v[k]) << endl;
        }
    }
    return 0;
}