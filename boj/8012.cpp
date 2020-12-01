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
const int MAXN = 30001;
int numToIdx[MAXN];
int numToDist[MAXN]; // root 로 부터의 거리
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

int main(){
    fastio;
    cin >> n;
    adj = vector<vector<pi> > (n+1);
    for(int i=0;i<n-1;++i){
        int u,v;
        cin >> u >> v;
        adj[u].push_back({v,1});
        adj[v].push_back({u,1});
    }
    memset(numToIdx,-1,sizeof(numToIdx));
    dfs(1,0);

    segTree = vector<int>(dfsVec.size()*4);
    seginit(1,0,dfsVec.size()-1);

    int m;
    cin >> m;
    int u,v;
    cin >> u;
    int ret = 0;
    rep(i,m-1){
        cin >> v;
        int le = numToIdx[u];
        int ri = numToIdx[v];
        if(le > ri) swap(le,ri);
        int lca = idxToNum[segquery(1,0,dfsVec.size()-1,le,ri)];
        ret += numToDist[u] + numToDist[v] - 2*numToDist[lca];
        u = v;
    }
    cout << ret;

    return 0;
}