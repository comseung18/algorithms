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

stack<int> st;
vi discovered;
int sccCounter, vertexCounter;
vi sccId;

// here 에서 역방향간선이나 교차간선을 통해
// 올라 갈 수 있는 가장 작은 vertexNumber 를 반환
int dfs(int here){
    int ret = discovered[here] = vertexCounter++;
    st.push(here);
    for(int there : adj[here]){
        // 트리 간선이면
        if(discovered[there] == -1) ret = min(dfs(there),ret);
        // 아직 scc 가 안만들어진 교차,역방향 간선이면
        if(sccId[there] == -1) ret = min(ret, discovered[there]);
    }
    // 이 간선을 끊을지 말지 결정한다.
    if(ret == discovered[here]){
        while(1){
            int t = st.top();
            st.pop();
            sccId[t] = sccCounter;
            if(t== here) break;
        }
        ++sccCounter;
    }
    return ret;
}
int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
        int N,M;
        cin >> N >> M;
        adj = vvi(N);
        rep(i,M){
            int x,y;
            cin >> x >> y;
            adj[x].push_back(y);
        }
        sccId = discovered = vi(N,-1);
        sccCounter = vertexCounter = 0;
        rep(i,N) if(discovered[i] == -1)
            dfs(i);
        // sccId 완성
        // inDegree 가 0 인 scc 를 찾아보자.
        vi inDegree(sccCounter,0);
        
        rep(here,N){
            for(int there : adj[here]){
                if(sccId[here] != sccId[there]){
                    inDegree[sccId[there]]++;
                }
            }
        }
        int cnt = 0;
        int inDegreeOneIndex = -1;
        rep(i,sccCounter) if(inDegree[i] == 0){
            ++cnt;
            inDegreeOneIndex = i;
        } 
        if(cnt == 1){
            rep(i,N) if(sccId[i] == inDegreeOneIndex) cout << i << endl;
        }else{
            cout << "Confused" << endl;
        }
        cout << endl;
    }
    return 0;
}