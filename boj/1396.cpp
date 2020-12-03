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

const int MAXN = 250001;
int numToIdx[MAXN];
int numToDist[MAXN]; // root 로 부터의 거리
int numToTemperature[MAXN]; // 이 노드에 오기 위한 온도 초기 값은 0
int numToSize[MAXN]; // 자식 단말 노드의 개수
vector<int> idxToNum;
vector<int> dfsVec;
int n;
vector<vector<pair<int,int> > > adj;
int idx;
void dfs(int here, int depth, int parent = -1, int dist = 0){
    dfsVec.push_back(depth);
    idxToNum.push_back(here);
    // here 을 최초방문
    if(numToIdx[here] == -1){
        numToIdx[here] = idx;
        numToDist[here] = dist;
    }
    ++idx;
    for(pair<int,int> there : adj[here]){
        if(numToIdx[there.first] == -1)
            dfs(there.first,depth+1,here,dist+there.second);
    }
    ++idx;
    if(parent != -1){
        dfsVec.push_back(depth-1);
        idxToNum.push_back(parent);
    }
}
vector<int> segTree;
int seginit(int num, int left, int right){
    
    if(left == right){
        return segTree[num] = left;
        
    }
    int mid = (left+right)/2;
    int t1 = seginit(num*2,left,mid);
    int t2 = seginit(num*2+1,mid+1,right);
    if(dfsVec[t1] < dfsVec[t2]){
        return segTree[num] = t1;
    }
    return segTree[num] = t2;
}
int segquery(int num,int left, int right, int x, int y){
    if(left > y || right < x) return INT_MAX;
    if(x <= left && right <= y){
        return segTree[num];
    }
    int mid = (left+right)/2;
    int t1 = segquery(num*2,left,mid,x,y);
    int t2 = segquery(num*2+1,mid+1,right,x,y);
    
    int a1 = t1;
    int a2 = t2;
    if(a1 ==  INT_MAX) a1 = INT_MAX;
    else a1 = dfsVec[a1];
    if(a2 == INT_MAX) a2 = INT_MAX;
    else a2 = dfsVec[a2];
    
    if(a1 < a2) return t1;
    else return t2;
}

struct DisjointSet{
    vector<int> parent;
    DisjointSet(int n): parent(n){
        for(int i=0;i<n;++i)
            parent[i] = i;
    }
    // u 가 속한 트리의 루트의 번호를 반환한다.
    int find(int u){
        if(u == parent[u] ) return u;
        return parent[u] = find(parent[u]);
    }
    // v 는 u 의 자식이 된다.
    void merge(int u, int v){
        u = find(u);
        v = find(v);
        if(u==v) return;
        parent[v] = u;
    }
};

// int numToTemperature[MAXN]; // 이 노드에 오기 위한 온도 초기 값은 0
// int numToSize[MAXN]; // 자식 단말 노드의 개수
int main(){
    fastio;
    int N,M; // 정점의 개수 N 과 간선의 개수 M
    cin >> N >> M;
    DisjointSet djs = DisjointSet(MAXN);
    adj = vector<vector<pair<int,int> > > (MAXN);
    int id = N+1;
    rep(i,N) numToSize[i+1] = 1;
    vector< pair<int, pi> > edges;
    rep(i,M){
        int a,b,c;
        cin >> a >> b >> c;
        edges.push_back({c, {a,b}});
    }
    sort(edges.begin(),edges.end());

    rep(i,M){
        int a,b,c;
	
        a = edges[i].second.first;
        b = edges[i].second.second;
        c = edges[i].first;
        if(djs.find(a) != djs.find(b)){
            int ta = djs.find(a);
            int tb = djs.find(b);
            numToSize[id] = numToSize[ta] + numToSize[tb];
            numToTemperature[id] = c;
            // a 와 b 를 이어주자
            djs.merge(ta,tb);
            djs.merge(id,ta);
            adj[id].push_back({ta,1});
            adj[id].push_back({tb,1});
            adj[ta].push_back({id,1});
            adj[tb].push_back({id,1});
            ++id;
        }
    }
    // 아직 컴포넌트에 포함 되지 않은 노드가 있다면 찾아서 union 해주자.
    const int INF = INT_MAX;
    for(int i=2;i<=N;++i){
        int a,b,c;
        a = 1;
        b = i;
        c = INF;
        if(djs.find(a) != djs.find(b)){
            int ta = djs.find(a);
            int tb = djs.find(b);
            numToSize[id] = numToSize[ta] + numToSize[tb];
            numToTemperature[id] = c;
            // a 와 b 를 이어주자
            djs.merge(ta,tb);
            djs.merge(id,ta);
            adj[id].push_back({ta,1});
            adj[id].push_back({tb,1});
            adj[ta].push_back({id,1});
            adj[tb].push_back({id,1});
            ++id;
        }
    }
    n = id-1;
    memset(numToIdx,-1,sizeof(numToIdx));
    dfs(id-1,0);

    segTree = vector<int>(dfsVec.size()*4);
    seginit(1,0,dfsVec.size()-1);
    int q;
    cin >> q;
    rep(i,q){
        int x,y;
        cin >> x >> y;
        int le = numToIdx[x];
        int ri = numToIdx[y];
        if(le > ri) swap(le,ri);
        int lca = idxToNum[segquery(1,0,dfsVec.size()-1,le,ri)];
        if(numToTemperature[lca] != INF)
	cout << numToTemperature[lca] << ' ' << numToSize[lca] << endl;
        else cout << -1 << endl;
    }
    return 0;
}