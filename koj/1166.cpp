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
        int a,b;
        cin>> a >> b;
        if(a>=0)
            cout << a%b << endl;
        else{
            a = -a;
            cout << (b - a%b)%b << endl;
        }
            
    }
    return 0;
}