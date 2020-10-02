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
    //fastio;
    int N,K;
    cin >> N >> K;
    queue<int> q;
    q.push(K);
    vi visit(100001,-1);
    visit[K] = 0;

    vi cnt(100001,0);
    cnt[K] = 1;
    while(!q.empty()){
        int here = q.front();
        q.pop();

        
        if(here+1 <= 100000 && visit[here+1] == -1){
            q.push(here+1);
            visit[here+1] = visit[here]+1;
        }
        if(here-1 >= 0 && visit[here-1] == -1){
            q.push(here-1);
            visit[here-1] = visit[here]+1;
        }
        if((here%2 == 0) && visit[here/2] == -1){
            q.push(here/2);
            visit[here/2] = visit[here]+1;
        }

        if(here+1 <= 100000 && visit[here] +1 == visit[here+1]){
            cnt[here+1] += cnt[here];
        }
        if(here-1 >= 0 && visit[here] +1 == visit[here-1]){
            cnt[here-1] += cnt[here];
        }
        if((here%2 == 0) && visit[here] +1 == visit[here/2]){
            cnt[here/2] += cnt[here];
        }
    }
    std::cout << visit[N] << endl << cnt[N] << endl;
    
    return 0;
}