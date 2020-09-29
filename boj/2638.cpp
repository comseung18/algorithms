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

int N,M;
int bo[101][101];
int bocp[101][101];

const int AIR = 3;
const int CHEASE = 1;
const int NOTVISIT = 0;

const int dir[4][2]={
    {1,0},{0,1},{-1,0},{0,-1}
};
inline bool isVal(int y, int x){
    if(y <0 || y >= N || x < 0 || x >= M) return false;
    return true;
}
// bo 를 이용해 bocp 에  공기를 표시
void dfs(int y, int x){
    bocp[y][x] = AIR;
    rep(d,4){
        int ny = y + dir[d][0];
        int nx = x + dir[d][1];
        if(isVal(ny,nx) && (bocp[ny][nx] == NOTVISIT)) dfs(ny,nx);
    }
}
int t = 0;
// onetime
void onetime(){
    ++t;
    rep(i,N) copy(bo[i],bo[i]+M,bocp[i]);
    dfs(0,0);
    // 치즈를 순회하며, 
    // 둘러싸인 공기의 개수가 2 이상이면
    // bocp[y][x] = NOTVISIT 으로 함.
    rep(y,N) rep(x,M) if(bocp[y][x] == CHEASE){
        int cnt = 0;
        rep(d,4){
            int ny = y + dir[d][0];
            int nx = x + dir[d][1];
            if(isVal(ny,nx) && bocp[ny][nx] == AIR) ++ cnt;
        }
        if(cnt >=2) bocp[y][x] = NOTVISIT;
    }

    memset(bo,0,sizeof(bo));
    // bocp 를 돌면서 아직 치즈인 애들을 bo 에 옮김
    rep(y,N) rep(x,M) if(bocp[y][x] == CHEASE) bo[y][x] = CHEASE;
}

// bo 에 남은 치즈의 개수 세기
int ch(){
    int s= 0;
    rep(y,N) rep(x,M) if(bo[y][x]) ++s;
    return s;
}
int main(){
    fastio;
    cin >> N >> M;
    rep(i,N) rep(j,M) cin >> bo[i][j];

    while(ch() != 0){
        
        onetime();
    }
    cout << t;
    return 0;
}