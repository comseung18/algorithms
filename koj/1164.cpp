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
const string A = "TSC";
const string B = "BRY";
const string C = "BWG";
int getIndex(char a, char b, char c){
    return A.find(a)*100 + B.find(b)*10 + C.find(c);
}
bool func(int a, int b, int c){
    if(a == b && b == c && c == a) return true;
    if(a!= b && b != c && c != a) return true;
    return false;
}
bool m[999];
// 합이 되는 개수를 반환
// 합이 되는 경우를 m 에 반환
int cal(const vi& v){
    int cnt = 0;
    for(int i=0;i<=6;++i)
        for(int j=i+1;j<=7;++j)
            for(int k=j+1;k<=8;++k){
                // 가능한지 검사.
                // 각 속성이 모두 같거나 모두 다른지?
                bool ch = true;
                // 도형검사
                ch = ch & (func(v[i]/100,v[j]/100,v[k]/100));
                // 도형색 검사
                ch = ch & (func((v[i]/10)%10,(v[j]/10)%10,(v[k]/10)%10));
                // 배경검사
                ch = ch & (func(v[i]%10,v[j]%10,v[k]%10));
                if(ch){
                    m[i*100+j*10+k] = true;
                    cnt++;
                } 
            }
    return cnt;
}
int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
        vi v(9);
        for(int i=0;i<9;++i){
            char a,b,c;
            cin >>a >> b >> c;
            v[i] = getIndex(a,b,c);
        }
        int u1 = 0, u2 = 0;
        memset(m,0,sizeof(m));
        int left_combi = cal(v);
        bool turnU1 = true;
        while(1){
            char c;
            cin >> c;
            if(c == 'G'){
                if(left_combi){
                    if(turnU1) u1 = max(0,u1-1);
                    else u2 = max(0,u2-1);
                    turnU1 = !turnU1;
                    continue;
                }
                else{
                    if(turnU1) u1 = u1+3;
                    else u2 = u2+3;
                    break;
                }
            }
            else if(c == 'T'){
                turnU1 = !turnU1;
                continue;
            }
            // H 란 뜻
            vi temp(3);
            rep(i,3) cin >> temp[i];
            std::sort(temp.begin(), temp.end());
            int s = 0;
            rep(i,3){
                s *= 10;
                s += (temp[i]-1);
            }
            // 이 조합이 실제로 있는지 알면 되겠지..
            if(m[s]){
                m[s] = false;
                --left_combi;
                if(turnU1) ++u1;
                else ++u2;
            }
            else{
                if(turnU1) u1 = max(0,u1-1);
                else u2 = max(0,u2-1);
            }

            turnU1 = !turnU1;
        }
        cout << u1 << ' ' << u2 << endl;
    }
    return 0;
}