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
    int N,M;
    cin >> N >> M;
    if(M <= 2) cout << "NEWBIE!";
    else if(M <= N) cout << "OLDBIE!";
    else cout << "TLE!";
    return 0;
}