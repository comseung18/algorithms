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

const int MOD = 1000000007;

class Mat{
    public:
    const static int R = 3;
    const static int C = 3;
    ll v[R][C]= {0};
    Mat(){
    }
    Mat operator*(const Mat& m){
        Mat ret = Mat();
        for(int i=0;i<R;++i){
            for(int j=0;j<C;++j){
                ll s =0;
                for(int k=0;k<R;++k) s += ((v[i][k]%MOD)*(m.v[k][j]%MOD))%MOD;
                ret.v[i][j] = s%MOD;
            }
        }
        return ret;
    }
    // n 승을 반환
    Mat pow(int n){
        // 불변식 n >= 0
        Mat ret = Mat();
        if(n==0){
            rep(i,R) ret.v[i][i] = 1;
            return ret;
        }
        // 홀수면
        if(n%2){
            return *this*pow(n-1);
        }
        // 짝수면
        ret = pow(n/2);
        return ret*ret;
    }
};
int main(){
    fastio;
    Mat m = Mat();
    m.v[0][1] = m.v[1][2] = m.v[2][0] = m.v[2][1] = m.v[2][2] = 1;
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        if(n <=3){
            cout << n << endl;
            continue;
        }
        Mat tmp = m.pow(n-1);
        int ans = 0;
        rep(i,3){
            ans += (tmp.v[0][i]*(i+1))%MOD;
            ans %= MOD;
        }
        cout << ans << endl;
    }
    return 0;
}