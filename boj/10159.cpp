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

int arr[101][101];
// arr[i][j] = 1 -> i 가 j 보다 무겁다.
// 0 -> i 가 j 보다 무겁지 않거나 관계를 알 수 없다.
int arr2[101][101];
// arr2[i][j] = 1 -> i 가 j 보다 가볍다.
// 0 -> i 가 j 보다 가볍지 않거나 관계를 알 수 없다.
int main()
{
    fastio;
    int N, M;
    cin >> N >> M;
    rep(i, M)
    {
        int a, b;
        cin >> a >> b;
        arr[a][b] = 1;
        arr2[b][a] = 1;
    }
    for (int k = 1; k <= N; ++k)
    {

        for (int i = 1; i <= N; ++i)
        {
            for (int j = 1; j <= N; ++j)
            {
                arr[i][j] = (arr[i][j] || (arr[i][k] && arr[k][j]));
                arr2[i][j] = (arr2[i][j] || (arr2[i][k] && arr2[k][j]));
            }
        }
    }
    for(int i=1;i<=N;++i){
        int cnt =0;
        for(int j=1;j<=N;++j) if(i != j && (arr[i][j] == 0
        && arr2[i][j] == 0)) ++ cnt;
        cout << cnt << endl;
    }
    return 0;
}