#include <bits/stdc++.h>
using namespace std;

const int dir[8][2]={
  {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}  
};
struct fireBall{
  int r,c,m,d,s;
  // (r,c) 는 위치
  // m 은 질량
  // d 는 방향
  // s 는 속력
  // id 는 자신의 index 정보
  fireBall(int _r, int _c, int _m, int _s, int _d)
  :r(_r),c(_c),m(_m),s(_s),d(_d){}
};

int mod(int n, int m){
    if(n <0) return (m-(-n)%m)%m;
    return n%m;
}
struct fireBalls{
    int n; // n 은 bo 의 크기 n*n 
    vector<fireBall> v;
    fireBalls(int _n) : n(_n){}
    
    void insert(const fireBall &f){
        v.push_back(f);
    }
    // 모든 파이어볼에게 이동을 명령함.
    void moveAll(){
        int tempM[51][51]={0}; // 합쳐진 파이어볼의 질량의 합
        int tempS[51][51]={0}; // 합쳐진 파이어볼의 속력의 합
        int tempCnt[51][51]={0}; // 합쳐진 파이어볼의 개수
        int tempD[51][51]={0}; // 파이어볼의 이동방향
        int tempDD[51][51]={0};
        // tempDD 에서 처음이면 0, 모두 홀수면 1 , 모두 짝수면 2, 홀짝 이 같이 있으면 3
        
        for(const fireBall &f : v){
            int nr = mod(f.r + dir[f.d][0]*f.s,n);
            int nc = mod(f.c + dir[f.d][1]*f.s,n);
            tempM[nr][nc] += f.m;
            tempS[nr][nc] += f.s;
            ++tempCnt[nr][nc]; 
            tempD[nr][nc] = f.d;
            if(tempDD[nr][nc]==0) tempDD[nr][nc] = (f.d%2 ? 1 : 2);
            else if(tempDD[nr][nc] == 1 && (f.d%2 == 0)) tempDD[nr][nc] = 3;
            else if(tempDD[nr][nc] == 2 && (f.d%2)) tempDD[nr][nc] = 3;
        }
        v.clear();
        for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
        if(tempCnt[i][j] >= 2){
            // 4 개의 파이어볼로 나누어 진다.
            int m = tempM[i][j]/5;
            if(m==0) continue;
            int s = ((tempS[i][j]/tempCnt[i][j]));
            int t = ((tempDD[i][j] == 1 || tempDD[i][j] == 2)? 0:1);
            for(int k=0;k<4;++k)
                v.push_back(fireBall(i,j,m,s,t+k*2));
        }else if(tempCnt[i][j] == 1){
            v.push_back(fireBall(i,j,tempM[i][j],tempS[i][j],tempD[i][j]));
        }
    }
    int massSum(){
        int ret = 0;
        for(const fireBall& f:v)
            ret += f.m;
        return ret;
    }
    
    void info(){
        int boM[51][51] = {0};
        int boS[51][51] = {0};
        int boD[51][51] = {0};
        for(const fireBall& f:v){
            boM[f.r][f.c] = f.m;
            boS[f.r][f.c] = f.s;
            boD[f.r][f.c] = f.d;
        }
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                printf("(%d, %d, %d) ",boM[i][j],boS[i][j],boD[i][j]);
            }
            cout << "\n\n";
        }
        cout << "======================\n";
    }
    
};
int main(){
    int N,M,K; // N 은 bo 의 크기 (NxN), M 은 파이어볼의 개수, K 는 이동을 하는 횟수
    cin >> N >> M >> K;
    fireBalls fbs(N);
    for(int i=0;i<M;++i){
        int r,c,m,s,d;
        cin >> r >> c >> m >> s >> d;
        --r; --c;
        s%=N;
        fbs.insert(fireBall(r,c,m,s,d));
    }
    
    for(int i=0;i<K;++i) fbs.moveAll();
    cout << fbs.massSum();
    
    
    return 0;
}