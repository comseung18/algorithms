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

struct pos{
    bool cliped;
    int clipCnt;
    int cnt;
    int t;
    pos(){}
    pos(bool a,int b, int c, int d)
    : cliped(a), clipCnt(b), cnt(c), t(d)
    {}
};
bool visit[2][2001][2001];

int main(){
    fastio;
    int s;
    cin >> s;
    queue<pos> q;
    q.push(pos(false,0,1,0));
    visit[0][0][1] = true;

    while(!q.empty()){
        pos p = q.front();
        q.pop();

        // 1. 복사를 하거나
        // 2. 붙여넣기를 하거나 ( 복사된 상태만 가능 )
        // 3. 한개를 지우거나
        if(p.cnt == s){
            cout << p.t;
            return 0;
        }

        // 복사하기
        if(p.cnt > 2000 ){}
        else if(!visit[1][p.cnt][p.cnt]){
            visit[1][p.cnt][p.cnt] = true;
            q.push(pos(true,p.cnt,p.cnt,p.t+1));
        }
        
        // 붙여넣기
        if(p.cliped){
            if(p.cnt+p.clipCnt > 2000) {

            }
            else if(!visit[1][p.clipCnt][p.cnt+p.clipCnt]){
                visit[1][p.clipCnt][p.cnt+p.clipCnt] = true;
                q.push(pos(true,p.clipCnt,p.cnt+p.clipCnt,p.t+1));
            }
        }
        // 한개지우기
        if(p.cnt >= 1){
            if(!visit[p.cliped][p.clipCnt][p.cnt-1]){
                visit[p.cliped][p.clipCnt][p.cnt-1] = true;
                q.push(pos(p.cliped,p.clipCnt,p.cnt-1,p.t+1));
            }
        }
    }
    return 0;
}