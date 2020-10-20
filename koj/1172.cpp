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
    int index,dir;
    int time;
    pos(){}
    pos(int i, int d, int t)
    :index(i),dir(d),time(t){}
};
int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
        string s;
        
        cin >> s;
        queue<pos> q;
        for(int i=0;i<s.size();i++){
            if(s[i] =='R') q.push(pos(i,1,0));
            else if(s[i] == 'L') q.push(pos(i,-1,0));
        }
        vi v = vi(s.size(),0);

        const int sz = s.size();
        while(!q.empty()){
            
            pos p = q.front();
            q.pop();
            
            
            // 범위를 나가면 무시
            if(p.index + p.dir < 0 || p.index + p.dir >= sz) continue;

            char c = ((p.dir == 1)? 'R':'L');
            // 이미 같은쪽으로 쓰러져 있으면 무시
            if(s[p.index+p.dir] == c) continue;

            // 이미 쓰러져 있는데 쓰러진 방향이 반대면 . 으로바꾸기
            if((s[p.index+p.dir] != '.') && (s[p.index+p.dir] != c)){
                // 내가 오기 전에 이미 쓰러져 있던거면 무시
                if(p.time >= v[p.index+p.dir]) continue;
                // . 으로 바꾸기
                s[p.index+p.dir] = '.';
                v[p.index+p.dir] = p.time+1;
                continue;
            }

            // 쓰러짐이 전파된다.
            s[p.index+p.dir] = c;
            v[p.index+p.dir] = p.time +1;
            q.push(pos(p.index+p.dir,p.dir,p.time+1));
        }
        cout << s << endl;
    }
    return 0;
}