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

// N에서 자기 자신을 찾으면서 나타나는 부분 일치를 이용해
// pi[]를 계산한다.
// pi[i]=N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이
vector<int> getPartialMatch(const string& N){
    int m = N.size();
    vector<int> pi(m,0);
    // KMP 로 자기자신을 찾는다.
    // N을 N에서 찾는다. begin = 0 이면 자기자신을 찾아버리니까 안됨!
    int begin =1, matched = 0;
    // 비교할 문자가 N의 끝에 도달할 떄까지 찾으면서 부분 일치를 모두 기록한다.
    while(begin+matched < m){
        if(N[begin+matched] == N[matched]){
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
    return pi;
}

int main(){
    fastio;
    while(1){
        string s;
        cin >> s;
        if(s==".") return 0;
        vi pi = getPartialMatch(s);
        int n = s.size();
        if(n%(n-pi[n-1]) == 0)
            cout << n /(n - pi[n-1]) << endl;
        else
            cout << 1 << endl;
    }
    return 0;
}