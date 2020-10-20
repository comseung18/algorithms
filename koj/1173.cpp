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
int gcd(int a, int b){
    if(b==0) return a;
    return gcd(b,a%b);
}
int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        int g;
        cin >> g;
        rep(i,n-1){
            int t;
            cin >> t;
            g = gcd(g,t);
        }
        cout << (g == 1? "true" : "false") << endl;

    }
    
    
    return 0;
}