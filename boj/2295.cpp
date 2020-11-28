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
    int N;
    cin >> N;
    vi v(N);
    rep(i,N) cin >> v[i];
    sort(v.begin(),v.end());
    vector<int>::iterator it;
    int ans = 0;
    for(int i=0;i<N;++i)
        for(int j=i;j<N;++j)
            for(int k=j;k<N;++k){
                it = lower_bound(v.begin()+k,v.end(),v[i]+v[j]+v[k]);
                if(it == v.end()) continue;
                if(*it == v[i]+v[j]+v[k]) ans = max(ans, *it);
            }
    cout << ans;

    return 0;
}