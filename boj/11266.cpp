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

vector<vector<int>> adj;
vector<int> discovered;
// 각 정점이 단절점인지 여부
vector<bool> isCutVertex;
int vertexCnt;

int dfs(int here, bool isRoot)
{
    int ret = discovered[here] = vertexCnt++;
    // 루트인 경우 절단점 판정을 위해 자손 서브트리의 개수를 센다.
    int children = 0;
    for (int there : adj[here])
    {
        if (discovered[there] == -1)
        {
            ++children;
            int subtree = dfs(there, false);
            if (!isRoot && subtree >= discovered[here])
                isCutVertex[here] = true;
            ret = min(ret, subtree);
        }
        else
            ret = min(ret, discovered[there]);
    }
    if (isRoot)
        isCutVertex[here] = (children >= 2);
    return ret;
}

int main()
{
    fastio;
    int V,E;
    cin >> V >> E;

    adj = vvi(V);
    discovered = vi(V,-1);
    isCutVertex = vb(V, false);

    rep(i,E){
        int x,y;
        cin >>x >> y;
        adj[--x].push_back(--y);
        adj[y].push_back(x);
    }
    rep(i,V) if(discovered[i] == -1) dfs(i,true);

    int cnt =0;
    rep(i,V) if(isCutVertex[i]) ++cnt;
    cout << cnt << endl;
    rep(i,V) if(isCutVertex[i]) cout << i+1 << ' ';
    return 0;
}