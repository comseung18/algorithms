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

vi sccId;
vi discovered;
int sccCounter, vertexCounter;
stack<int> st;

void init(int n){
    sccId = discovered = vi(n,-1);
    sccCounter = vertexCounter = 0;
}
int scc(int here){
    int ret = discovered[here] = vertexCounter++;
    st.push(here);

    for(int there: adj[here]){
        if(discovered[there] == -1) ret = min(ret, scc(there));
        if(sccId[there] == -1) ret = min(ret, discovered[there]);
    }
    if(ret == discovered[here]){
        while(1){
            int t = st.top();
            st.pop();
            sccId[t] = sccCounter;
            if(t == here) break;
        }
        ++sccCounter;
    }

    return ret;
}
int main(){
    fastio;
    int N,M,S,T;
    cin >> N >> M >> S >> T;
    --S; --T;
    adj = vvi(N);
    rep(i,M){
        int x,y;
        cin >> x >> y;
        adj[--x].push_back(--y);
    }
    init(N);
    rep(i,N) if(discovered[i] == -1) scc(i);

    vi sccSize = vi(sccCounter,0); // 각 scc 에 있는 노드의 개수
    vb canReach = vb(sccCounter, false); // S 가 속한 scc 로 부터 올 수 있는 scc 인지 여부
    vi sMax = vi(sccCounter, 0); // S에서 각 scc 까지 합한 경로 상 최대 노드 수
    vvi sadj = vvi(sccCounter);
    rep(here,N){
        sccSize[sccId[here]]++;
        set<int> tmp;
        for(int there : adj[here]) if(sccId[here] != sccId[there]){
            if(tmp.find(sccId[there]) == tmp.end()){
                tmp.insert(sccId[there]);
                sadj[sccId[here]].push_back(sccId[there]);
            }
        }
    } 

    canReach[sccId[S]] = true;
    for(int here = sccId[S];here>=0;--here){
        if(!canReach[here]) continue;
        sMax[here] += sccSize[here];
        for(int there : sadj[here]){
            canReach[there] = true;
            sMax[there] = max(sMax[there], sMax[here]);
        }
    } 
    if(!canReach[sccId[T]]) cout << 0 << endl;
    else cout << sMax[sccId[T]] << endl;

    return 0;
}