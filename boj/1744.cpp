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
    vi p,m;
    rep(i,n){
        int t;
        cin >> t;
        if(t > 0) p.push_back(t);
        else m.push_back(t);
    }
    sort(p.rbegin(),p.rend());
    sort(m.begin(),m.end());
    int s = 0;
    for(int i=0;i<(int)p.size()-1;i+=2){
        if(p[i]*p[i+1] > p[i] + p[i+1]){
            s += p[i]*p[i+1];
        }
        else{
            s += p[i] + p[i+1];
        }
    }
    if(p.size()%2) s+=p.back();
    for(int i=0;i<(int)m.size()-1;i+=2){
        s += m[i]*m[i+1];
    }
    if(m.size()%2) s += m.back();

    cout << s;

    return 0;
}