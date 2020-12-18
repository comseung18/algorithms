#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vector<int>> vvi;

#define endl '\n'
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define fastio                    \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);

// 그래프의 인접 리스트 표현
vector<vector<int>> adj;
// 각 정점의 컴포넌트 번호. 컴포넌트 번호는 0부터 시작하며,
// 같은 강결합 컴포넌트에 속한 정점들의 컴포넌트 번호가 같다.
vector<int> sccId;
// 각 정점의 발견 순서
vector<int> discovered;
// 정점의 번호를 담는 스택
stack<int> st;
int sccCounter, vertexCounter;
// here를 루트로 하는 서브트리에서 역방향 간선이나 교차간선을
// 통해 갈 수 있는 정점 중 최소 발견 순서를 반환한다
// (이미 scc로 묶인 정점으로 연결된 교차 간서은 무시한다)
int scc(int here)
{
    int ret = discovered[here] = vertexCounter++;
    // 스택에 here를 넣는다. here 의 후손들은 모두 스택에서 here 후에 들어간다.
    st.push(here);
    for (int there : adj[here])
    {
        // (here, there) 가 트리간선
        if (discovered[there] == -1)
            ret = min(ret, scc(there));
        // there가 무시해야 하는 교차간선이 아니라면
        else if (sccId[there] == -1)
            ret = min(ret, discovered[there]);
    }
    // here에서 부모로 올라가는 간선을 끊어야 할지 확인한다.
    if (ret == discovered[here])
    {
        // here 를 루트로 하는 서브트리에 남아있는 정점들을 전부 하나의 컴포넌트로 묶는다.
        while (1)
        {
            int t = st.top();
            st.pop();
            sccId[t] = sccCounter;
            if (t == here)
                break;
        }
        ++sccCounter;
    }
    return ret;
}

// tarjan의 SCC 알고리즘
vector<int> tarjanSCC()
{
    // init
    sccId = discovered = vector<int>(adj.size(), -1);
    sccCounter = vertexCounter = 0;
    // 모든 정점에 대해서 scc()
    for (int i = 0; i < adj.size(); ++i)
        if (discovered[i] == -1)
            scc(i);
    return sccId;
}

vvi sadj;
vi scash;
vb sHasRes;
vi sMax;
vb sReach;
vi cash;
vb hasRes;
int main()
{
    fastio;
    int N, M; // 교차로와 도로의 수
    cin >> N >> M;
    adj = vvi(N);
    rep(i,M){
        int x,y;
        cin >> x >> y;
        adj[--x].push_back(--y);
    }
    cash = vi(N,0);
    rep(i,N) cin >> cash[i];

    int S,P;
    cin >> S >> P;
    --S;
    hasRes = vb(N);
    rep(i,P){
        int t;
        cin >> t;
        hasRes[--t] = true;
    }
    
    tarjanSCC();
    // sccId 에 정점의 scc 정보가 들어있다.
    // 이 때, sccId 의 역순으로 정렬하면,
    // 위상정렬의 결과가 얻어진다.
    sadj = vvi(sccCounter);
    scash = vi(sccCounter,0);
    sHasRes = vb(sccCounter,false);
    sMax = vi(sccCounter,0);
    rep(here,N){
        scash[sccId[here]] += cash[here];
        set<int> tmp;
        if(hasRes[here]) sHasRes[sccId[here]] = true;
        for(int there: adj[here]){
            if(sccId[here] != sccId[there]){
                if(tmp.find(there) == tmp.end()){
                    sadj[sccId[here]].push_back(sccId[there]);
                    tmp.insert(there);
                }
                
            }
        }
    }

    sReach = vb(sccCounter,0); // 시작점에서 여기 까지 도달할수 있는가
    sReach[sccId[S]] =true;
    for(int here = sccId[S];here>=0;--here){
        if(!sReach[here]) continue;
        sMax[here] += scash[here];
        for(int there : sadj[here]){
            sMax[there] = max(sMax[there],sMax[here]);
            sReach[there] = true;
        }
    }

    int ans = 0;
    rep(i,sccCounter){
        if(sHasRes[i] && sReach[i]) ans = max(ans, sMax[i]);
    }
    cout << ans << endl;
    return 0;
}