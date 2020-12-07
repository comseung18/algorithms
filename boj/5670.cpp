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
inline int toNumber(char ch) { return ch - 'a'; }

struct TrieNode{
    unordered_map<int,TrieNode*> children;
    // 이 노드가 종료노드인가?
    bool terminal;
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
    void insert(const char* key){
        // 문자열이 끝나면 terminal만 참으로 바꾸고 종료
        if(*key ==0)
            terminal = true;
        else{
            int next = toNumber(*key);
            TrieNode** it  = &children[next];
            if(*it == NULL){
                *it = new TrieNode();
                ++childSize;
            }
            (*it)->insert(key+1);
        }
    }
    // 문자열 key 를 입력하는데 버튼을 눌러야 하는 횟수를 반환
    int type(const char* key){
        if(*key ==0) return 0;
        int next = toNumber(*key);
        if(childSize == 1 && !terminal) return children[next]->type(key+1);
        return children[next]->type(key+1)+1;
    }
};

int main(){
    fastio;
    int N;
    cout << fixed;
    cout.precision(2);
    while(cin >> N){
        vector<string> v(N);
        TrieNode* root = new TrieNode();
        rep(i,N){
            cin >> v[i];
            root->insert(v[i].c_str());
        }
        if(root->childSize == 1) root->childSize = 2; 
        int total = 0;
        rep(i,N){
            total += root->type(v[i].c_str());
        }
        cout << total/(double)N << endl;
    }
    return 0;
}