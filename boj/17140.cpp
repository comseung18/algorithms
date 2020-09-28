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

int bo[101][101];
int R,C,K; // bo[R][C] == k
bool cmp(const pi& p1, const pi& p2){
    // first 는 등장 횟수
    if(p1.first != p2.first) return p1.first < p2.first;
    // second 는 수
    return p1.second < p2.second;
}
int main(){
    fastio;
    cin >> R >> C >> K;
    --R; --C;
    rep(i,3) rep(j,3) cin >> bo[i][j];
    int cnt =0;

    int nowR = 3, nowC = 3; // 0이 아닌 원소로 이루어진 가장긴 행과 열
    // 의 값
    pi tmpCnt[101];
    while(bo[R][C] != K){
        ++cnt;
        if(cnt > 100){
            cout << -1; return 0;
        }
        
        if(nowR >= nowC){
            nowC =0;
            for(int i=0;i<nowR;i++){
                for(int j=1;j<=100;++j) tmpCnt[j] = {0,j};
                for(int j=0;j<100;j++) if(bo[i][j]) tmpCnt[bo[i][j]].first++;
                sort(tmpCnt+1,tmpCnt+101,cmp);
                int idx =0;
                for(int j=1;j<=100;++j){
                    if(tmpCnt[j].first == 0) continue;
                    if(idx >= 100) break;
                    bo[i][idx++] = tmpCnt[j].second;
                    if(idx >= 100) break;
                    bo[i][idx++] = tmpCnt[j].first;
                }
                for(int j=idx;j<100;++j) bo[i][j] = 0;
                nowC = max(nowC, idx);
            }
        }else{
            nowR = 0;
            // 열연산을 수행
            for(int i=0;i<nowC;i++){
                for(int j=1;j<=100;++j) tmpCnt[j] = {0,j};
                for(int j=0;j<100;j++) if(bo[j][i]) tmpCnt[bo[j][i]].first++;
                sort(tmpCnt+1,tmpCnt+101,cmp);
                int idx =0;
                for(int j=1;j<=100;++j){
                    if(tmpCnt[j].first == 0) continue;
                    if(idx >= 100) break;
                    bo[idx++][i] = tmpCnt[j].second;
                    if(idx >= 100) break;
                    bo[idx++][i] = tmpCnt[j].first;
                }
                for(int j=idx;j<100;++j) bo[j][i] = 0;
                nowR = max(nowR, idx);
            }
        }
    }
    cout << cnt;
    return 0;
}