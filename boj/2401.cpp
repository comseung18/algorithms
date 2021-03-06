#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vector<int>> vvi;

#define endl '\n'
#define rep(i,n) for(int i=0;i<(n);++i)
#define fastio ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);

int n;
string L,l;
int len[501];// len[i] 는 i번쨰 문자의 길이
bool v[501][100001]; // v[i][j] 는 i번째 문자를 L[i] 에서 붙일 수 있는가
int cache[100001]; // dp[pos] 는 pos 부터 붙여 넣을 수 있는 짧은 문자열의 총합의 최대 값
int pi[10001];

// N에서 자기 자신을 찾으면서 나타나는 부분 일치를 이용해
// pi[]를 계산한다.
// pi[i]=N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이
void getPartialMatch(){
    int m = l.size();
    memset(pi,0,sizeof(pi));
    // KMP 로 자기자신을 찾는다.
    // N을 N에서 찾는다. begin = 0 이면 자기자신을 찾아버리니까 안됨!
    int begin =1, matched = 0;
    // 비교할 문자가 N의 끝에 도달할 떄까지 찾으면서 부분 일치를 모두 기록한다.
    while(begin+matched < m){
        if(l[begin+matched] == l[matched]){
            ++matched;
            pi[begin+matched-1] = matched;
        }
        else{
            if(matched == 0)
                ++begin;
            else{
                begin += matched - pi[matched-1];
                matched = pi[matched-1];
            }
        }
    }
    return;
}
int nn;
// 짚더미 H의 부분 문자열로 바늘 N이 출현하는 시작 위치들을 모두 반환한다.
void kmpSearch(int id){
    int m = l.size();
    //pi[i] 는 N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이
    getPartialMatch();
    // begin = matched = 0 에서 부터 시작하자.
    int begin =0, matched = 0;
    while(begin <= nn-m){
        // 만약 짚더미의 해당 글자가 바늘의 해당 글자와 같다면
        if(matched < m && L[begin+matched] == l[matched]){
            ++matched;
            // 결과적으로 m글자가 모두 일치했다면 답에 추가한다.
            if(matched == m) v[id][begin] = true;
        }
        else{
            // 예외: matched가 0인 경우에는 다음 칸에서 부터 계속
            if(matched ==0)
                ++begin;
            else{
                begin += matched - pi[matched-1];
                //begin을 옮겼다고 처음부터 다시 비교할 필요가 없다.
                // 옮긴 후에도 pi[matched-1] 만큼은 항상 일치하기 때문이다.
                matched = pi[matched-1];
            }
        }
    }
    return;
}

int dp(int pos){
    if(pos >= L.size()) return 0;
    int & ret = cache[pos];
    if(ret != -1) return ret;

    ret = 0;
    rep(i,n){
        if(!v[i][pos]) continue;
        int tmp = pos + len[i];
        ret = max(ret, dp(tmp) + len[i]);
    }
    ret = max(ret,dp(pos+1));
    return ret;
}
int main(){
    fastio;
    cin >> L;
    cin >> n;
    nn = L.size();
    rep(i,n){
        cin >> l;
        len[i] = l.size();
        kmpSearch(i);
    }
    memset(cache,-1,sizeof(cache));
    cout << dp(0);
    return 0;
}