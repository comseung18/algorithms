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

const int MAXN = 100001;
int numToIdx[MAXN];

vector<int> idxToNum;
vector<int> dfsVec;
int n;
vector<vi> adj;
int idx;
void dfs(int here, int depth, int parent = -1){
    dfsVec.push_back(depth);
    idxToNum.push_back(here);
    // here 을 최초방문
    if(numToIdx[here] == -1){
        numToIdx[here] = idx;
    }
    ++idx;
    for(int there : adj[here]){
        if(numToIdx[there] == -1)
            dfs(there,depth+1,here);
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
    adj = vector<vi>(n+1);
    rep(i,n-1){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    memset(numToIdx, -1,sizeof(numToIdx));
    dfs(1,0);
    
    // idxToNum, dfsVec, numToIdx 가 완성됨.
    segTree = vi(dfsVec.size()*4);
    
    seginit(1,0,dfsVec.size()-1);

    int m;
    cin >> m;
    rep(i,m){
        int u,v;
        cin >> u >> v;
        int le = numToIdx[u];
        int ri = numToIdx[v];
        if(le > ri) swap(le,ri);
        // le <= ri
        cout << idxToNum[segquery(1,0,dfsVec.size()-1,le,ri)] << endl;
    }
    return 0;
}