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

vvi adj;
int wordCnt;
unordered_map<string, int> wordNum;

int sccCnt,vertexCnt;
vi discovered;
vi sccId;
stack<int> st;

void init(){
    adj = vvi();
    wordCnt = 0;
    wordNum = unordered_map<string,int>();
}
void init2(){
    sccCnt = vertexCnt = 0;
    discovered = sccId = vi(wordCnt, -1);
}
vector<string> split(string input, char delimiter){
    vector<string> ret;
    stringstream ss(input);
    string t;
    while(getline(ss,t,delimiter)) ret.push_back(t);
    return ret;
}
int scc(int here){
    int ret = discovered[here] = vertexCnt++;
    st.push(here);

    for(int there : adj[here]){
        if(discovered[there] == -1) ret= min(ret, scc(there));
        if(sccId[there] == -1) ret = min(ret, discovered[there]);
    }

    if(ret == discovered[here]){
        while(1){
            int t= st.top();
            st.pop();
            sccId[t] = sccCnt;
            if( t== here ) break;
        }
        sccCnt++;
    }
    return ret;
}
int main(){
    //fastio;
    int n;
    while(cin >> n){
        getchar();
        if(n==0) continue;
        init();
        rep(i,n){
            string line;
            getline(cin,line);
            vector<string> words = split(line,' ');
            if(wordNum.find(words[0]) == wordNum.end()){
                wordNum[words[0]] = wordCnt++;
                adj.push_back(vi());
            }
            int here = wordNum[words[0]];
            for(int i=1;i<words.size();++i){
                if(wordNum.find(words[i]) == wordNum.end()){
                    wordNum[words[i]] = wordCnt++;
                    adj.push_back(vi());
                }
                int there = wordNum[words[i]];
                adj[there].push_back(here);
            }
        }
        init2();
        rep(i,wordCnt) if(discovered[i] == -1) scc(i);

        vi sccIndegree(sccCnt,0);
        vi sccSize(sccCnt,0);

        rep(here,wordCnt){
            sccSize[sccId[here]]++;
            for(int there : adj[here]){
                if(sccId[here] != sccId[there]){
                    sccIndegree[sccId[there]]++;
                }
            }
        }
        // 크기가 2 이상인 scc 로 향하는 노드인지 여부
        vb sccTo2(sccCnt,false);
        rep(id,sccCnt){
            if(sccSize[id] >= 2){
                sccTo2[id] = true;
                continue;
            }
            for(auto it = wordNum.begin();it!=wordNum.end();++it)
                    if(sccId[it->second] == id){
                        int here = it->second;
                        for(int there : adj[here]){
                            if(sccSize[sccId[there]] >=2 || sccTo2[sccId[there]]){
                                sccTo2[sccId[here]] = true;
                                break;
                            }
                        }
                    }
        }
        vector<string> ans;
        for(int here = sccCnt-1;here >= 0; --here){
            if((sccIndegree[here] == 0) || sccTo2[here]){
                for(auto it = wordNum.begin();it!=wordNum.end();++it)
                    if(sccId[it->second] == here) ans.push_back(it->first);
            }
        }
        sort(ans.begin(),ans.end());
        std::cout << ans.size() << endl;
        for(string s : ans) std::cout << s << ' ';
        std::cout << endl;
    }
    return 0;
}