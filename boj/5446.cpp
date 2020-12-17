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
const int ALPHABETS = 63;
int toNumber(char ch){
    if(islower(ch)) return ch-'a';
    if(isupper(ch)) return ch-'A' + 26;
    if(ch  == '.') return 52;
    return ch-'0' + 53;
}

struct TrieNode{
    TrieNode* children[ALPHABETS];
    // 이 노드가 종료노드인가?
    bool terminalErase;
    bool terminalNotErase;
    // 이 노드를 루트로 하는 서브트리에 
    // 지워야하는 문자가 존재하는가?
    bool exErase;
    bool exNotErase;
    TrieNode() : terminalErase(false),terminalNotErase(false),exErase(false),exNotErase(false){
        memset(children, 0, sizeof(children));
    }
    ~TrieNode(){
        for(int i=0;i<ALPHABETS;++i)
            if(children[i])
                delete children[i];
    }
    // 이 노드를 루트로 하는 트라이에 문자열 key 를 추가한다.
    // key 는 지워야 하는 문자열이다.
    void insert(const char* key,bool erase){
        // 문자열이 끝나면 terminal만 참으로 바꾸고 종료
        if(*key ==0){
            if(erase) terminalErase = true;
            else terminalNotErase = true;
        }
        else{
            int next = toNumber(*key);
            if(children[next] == NULL){
                children[next] = new TrieNode();
            }
            if(erase) children[next]->exErase = true;
            else children[next]->exNotErase = true;

            children[next]->insert(key+1,erase);
        }
    }
    // 현재 노드를 루트로 하는 Trie 에서
    // rm 을 사용하여 지워야 하는 문자열들을 지울 때
    // rm 의 횟수, 단 지우면 안되는 문자열도 있음을 주의
    int rmCnt(){
        // 지워야하는 파일이 존재하지 않으면
        if(!exErase) return 0;
        // 지워야하는 파일은 존재하지만 
        // 지우면 안되는 파일이 없으면,
        // rm P* 하면되므로
        if(!exNotErase) return 1;

        // 재귀로 호출
        int ret =0;
        rep(i, ALPHABETS){
            if(children[i] != NULL){
                ret += children[i]->rmCnt();
            }
        }
        return ret + terminalErase;
    }
};

int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
        int n1;
        TrieNode* root = new TrieNode();
        root->exErase = true;
        cin >> n1; // 지워야 하는 파일의 개수
        rep(i,n1){
            string s;
            cin >> s;
            root->insert(s.c_str(),true);
        }
        int n2;
        cin >> n2; // 지우면 안되는 파일의 개수
        if(n2) root->exNotErase = true;
        rep(i,n2){
            string s;
            cin >> s;
            root->insert(s.c_str(),false);
        } 
        // 지우고 싶은 파일들을 모두 지우는데 필요한 최소 rm 명령회수
        cout << root->rmCnt() << endl;
        root->~TrieNode();
    }
    return 0;
}