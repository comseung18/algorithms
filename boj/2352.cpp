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
    vi v;
    while(n--){
        int t;
        cin >> t;
        if(v.empty() || v.back()<t) v.push_back(t);
        else{
            auto it = lower_bound(v.begin(),v.end(),t);
            *it = t;
        }
    }
    cout << v.size();
    return 0;
}