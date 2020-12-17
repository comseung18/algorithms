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
vi getFactor(int n){
    if(n < 0) n = -n;
    int m = (int)sqrt(n);
    vi ret;
    for(int i=1;i<m;++i){
        if(n%i == 0){
            ret.push_back(i);
            ret.push_back(-i);
            ret.push_back(n/i);
            ret.push_back(-(n/i));
        }
    }
    if(m*m == n){
        ret.push_back(m);
        ret.push_back(-m);
    } 
    return ret;
}
int main(){
    fastio;
    int a,c;
    cin >> a >> c;
    if(a==c){
        cout << "INF";
        return 0;
    }
    vi factor = getFactor(c-a);
    vector<pi> ans;
    for(int t : factor){
        int x = t-1;
        int y = -a*x+a+(c-a)/(1+x);
        ans.push_back({x,y});
    }
    sort(ans.begin(),ans.end());
    if(ans.empty()){
        cout << -1;
        return 0;
    }
    cout << ans[0].first << ' ' << ans[0].second;
    return 0;
}