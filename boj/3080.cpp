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

const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; }

const ll MOD = 1000000007;
ll fact[3500]={1};

struct TrieNode{
    unordered_map<int,TrieNode*> children;
    // 이 노드가 종료노드인가?
    int terminal;
    // 이 노드의 자식 개수
    int childSize;
    TrieNode() : terminal(false), childSize(0){
    }
    ~TrieNode(){
        for(auto it = children.begin();it!=children.end();++it){
            delete it->second;
        }
    }
    // 이 노드를 루트로 하는 트라이에 문자열 key 를 추가한다.
    // ov 길이 까지만 추가하고 그 뒤는 terminal 개수만 증가시킴.
    void insert(const char* key, int ov, int idx = 0){
        // 문자열이 끝나면 terminal만 참으로 바꾸고 종료
        if(*key ==0)
            ++terminal;
        else if(ov== idx)
            ++terminal;
        else{
            int next = toNumber(*key);
            TrieNode** it  = &children[next];
            if(*it == NULL){
                *it = new TrieNode();
                ++childSize;
            }
            (*it)->insert(key+1,ov,idx+1);
        }
    }
    ll cal(){
        ll tmp = 1;
        for(auto it = children.begin();it!=children.end();++it){
            tmp *= it->second->cal();
            tmp %= MOD;
        }
        return (tmp*fact[childSize+terminal])%MOD;
    }
};
vector<string> v;
int overlap(int i, int j){
    int n = min(v[i].size(),v[j].size());
    int ret = 0;
    rep(k,n) if(v[i][k] == v[j][k]) ++ret; else break;
    
    return ret;
}
int main(){
    fastio;
    rep(i,3500) if(i>0) fact[i] = (fact[i-1]*i)%MOD;
    TrieNode* root = new TrieNode();
    int N;
    cin >> N;
    v = vector<string>(N);
    rep(i,N) cin >> v[i];
    sort(v.begin(),v.end());
    rep(i,N){
        int lo=0,ro=0,o;
        if(i>0) lo = overlap(i,i-1);
        if(i<N-1) ro = overlap(i,i+1);
        o = max(lo,ro);
        root->insert(v[i].c_str(),o);
    }
    cout << root->cal();

    return 0;
}