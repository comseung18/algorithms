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

// 각 접미사들의 첫 t글자를 기준으로 한 그룹번호가 주어질 때,
// 주어진 두 접미사를 첫 2*t 글자를 기준으로 비교한다.
// group[] 은 길이가 0인 접미사도 포함한다.
struct Comparator{
    const vector<int>& group;
    int t;
    Comparator(const vector<int> &_group, int _t):
    group(_group), t(_t) {}

    bool operator() (int a, int b){
        // 첫 t 글자가 다르면 이들을 이용해 비교한다.
        if(group[a] != group[b]) return group[a] < group[b];

        // 아니라면 S[a+t..] 와 S[b+t..]의 첫 t글자를 비교한다.
        return group[a+t] < group[b+t];
    }
};

// s의 접미사 배열을 계산한다.
vector<int> getSuffixArray(const string& s){
    int n = s.size();
    // group[i]=접미사들을 첫 t글자를 기준으로 정렬했을 때,
    // s[i..] 가 들어가는 그룹의 번호
    // t =1 일 때는 정렬할 것 없이 s[i..]의 첫 글자로 그룹 번호를
    // 정해 줘도 같은 효과가 있다.
    int t = 1;
    vector<int> group(n+1);
    for(int i=0;i<n;++i) group[i] = s[i];
    group[n] = -1;
    // 결과적으로 접미사 배열이 될 반환 값. 이 배열을 lg(n)번 정렬한다.
    vector<int> perm(n);
    for(int i=0;i<n;++i) perm[i] = i;
    while(t<n){
        // group[]은 첫 t글자를 기준으로 계산해 뒀다.
        // 첫 2t 글자를 기준으로 perm을 다시 정렬한다.
        Comparator compareUsing2T(group, t);
        sort(perm.begin(), perm.end(), compareUsing2T);
        // 2t 글자가 n을 넘는다면 이제 접미사 배열 완성!
        t *= 2;
        if(t >= n) break;
        // 2t 글자를 기준으로 한 그룹 정보를 만든다
        vector<int> newGroup(n+1);
        newGroup[n] = -1;
        newGroup[perm[0]] = 0;
        for(int i=1;i<n;++i)
            if(compareUsing2T(perm[i-1],perm[i]))
                newGroup[perm[i]] = newGroup[perm[i-1]] +1;
            else
                newGroup[perm[i]] = newGroup[perm[i-1]];
        group = newGroup;
    }
    return perm;
}

// SA 가 s 의 suffixArray 일 때,
// LCP Array 를 반환함.
// lcp[k] = lcp(k-1,k)
// lcp[0] 은 정의되지 않음.
vector<int> getLCPArray(const string& s, const vector<int>& sa){
    int n = s.size();

    // rank 배열에는 접미사 배열 순서가 들어간다.
    vector<int> rank(n);
    for(int i=0;i <n; ++i ) rank[sa[i]] = i;

    int len = 0;
    vector<int> lcp(n);

    for(int i=0;i<n;i++){
        int k = rank[i];
        if(k){
            int j = sa[k-1];
            while(s[j+len] == s[i + len]) ++len;
            lcp[k] = len;

            if(len) --len;
        }
    }
    return lcp;
}

int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
        string s;
        cin >> s;
        vi sa = getSuffixArray(s);
        vi lcp = getLCPArray(s,sa);

        int ans = 0;
        int n = s.size();

        for(int i=0;i<n;i++){
            int cp =0;
            if(i > 1) cp = (lcp[i] >lcp[i-1]? 
            lcp[i]-lcp[i-1] : 0);
            else cp = lcp[i];
            ans += cp;
        }
        cout << ans << endl;
    }
    return 0;
}
