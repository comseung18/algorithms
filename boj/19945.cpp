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
    if(n==0){
        cout << 1;
        return 0;
    } 
    else if(n < 0){
        cout << 32;
        return 0;
    } 
    int cnt =0;
    while(n){
        ++cnt;
        n = n >> 1;
    }
    cout << cnt;
    return 0;
}