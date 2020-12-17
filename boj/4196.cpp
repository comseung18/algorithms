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
vector<bool> visited;
vi res;
// 위상정렬의 결과를 res 에 반환
void dfs(int here)
{
    visited[here] = true;
    for (int there : adj[here])
    {
        if (!visited[there])
            dfs(there);
    }
    res.push_back(here);
}
void topologicalSort()
{
    visited = vector<bool>(adj.size(), false);
    res = vector<int>();
    for (int i = 0; i < adj.size(); ++i)
        if (!visited[i])
            dfs(i);
    reverse(res.begin(), res.end());
}
int main()
{
    fastio;
    int T;
    cin >> T;
    while (T--)
    {
        int N,M;
        cin >> N >> M;
        adj = vector<vector<int> >(N);
        rep(i,M){
            int x,y;
            cin >> x >> y;
            adj[--x].push_back(--y);
        }
        topologicalSort();
        // res 에 위상정렬 결과가 반영된 상태
        int ans = 0;
        visited = vector<bool>(N, false);
        for(int i : res) if(!visited[i]){
            ++ans;
            dfs(i);
        }
        cout << ans << endl;
    }
    return 0;
}