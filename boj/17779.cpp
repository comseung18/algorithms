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

int N;
vvi A;
vvi copyA;

// 인구수가 가장 많은 선거구와 가정 적은 선거구의 차이를 계산
int cal(){
  int cnt[6] = {0};
  for(int i=1;i<=N;++i) for(int j=1;j<=N;++j)
    cnt[copyA[i][j]] += A[i][j];
  
  int ma = 0;
  int mi = 200000;
  for(int i=1;i<=5;++i){
    if(cnt[i] == 0) return -1;
    ma = max(ma,cnt[i]);
    mi = min(mi,cnt[i]);
  }
  return abs(ma-mi);
}
// 선거구 분할
void seperate(int x, int y, int d1, int d2){
  // 5 부터 표시
  for(int i=0;i<=d1;++i){
    int _x = x + i;
    int _y = y - i;

    for(int j=0;j<=d2;++j){
      copyA[_x+j][_y+j] = 5;
    }
    if(i != d2){
      ++_x;
      for(int j=0;j<d1;++j){
       copyA[_x+j][_y+j] = 5;
      }
    }
  }

  for(int r=1;r<=N;++r) for(int c=1;c<=N;++c) if(copyA[r][c] != 5){
    if(r<x+d1 && c <= y) copyA[r][c] = 1;
    else if(r<=x+d2 && y < c) copyA[r][c] =2;
    else if(x+d1 <= r && c < y-d1+d2) copyA[r][c] =3;
    else if(x+d2 < r && y-d1+d2 <= c ) copyA[r][c] = 4;
  }
  return;
}
int main(){
    fastio;
    cin >> N;
    A = vvi(N+1,vi(N+1));
    

    rep(i,N) rep(j,N) cin >> A[i+1][j+1];
    
    int ans = 987654321;
    for(int x=1;x<=N;++x){
        for(int y=1;y<=N;++y){
            for(int d1=1;d1<=N;++d1){
                for(int d2=1;d2<=N;++d2){
                    if(x+d1+d2 > N) continue;
                    if(1 > y-d1) continue;
                    if(y+d2 > N) continue;
                    copyA = vvi(N+1,vi(N+1));
                    seperate(x,y,d1,d2);
                    ans = min(ans, cal());
                }
            }
        }
    }
    cout << ans;
    return 0;
}