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
int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
      int N;
      cin >> N;
      if(N==1){
        cout << 1 << endl;
        continue;
      }
      vi parent = vi(N,-1);
      queue<int> q;

      parent[1] = 1;
      q.push(1);

      while(!q.empty() || parent[0] == -1){
        int m = q.front();
        q.pop();

        rep(i,2){
          int next = (m*10 + i)%N;
          if(parent[next] == -1){
            parent[next] = m;
            q.push(next);
          }
        }
      }

      if(parent[0] == -1){
        cout << "BRAK\n";
        continue;
      }
      string s;
      for(int m=0; m != parent[m]; m = parent[m]){
        rep(i,2){
          int next = (parent[m]*10 + i)%N;
          if(next == m){
            s.push_back(i + '0');
            break;
          } 
        }
      }
      s.push_back('1');
      reverse(s.begin(),s.end());
      cout <<s << endl;
      
    }
    return 0;
}