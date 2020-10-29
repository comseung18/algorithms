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

unordered_map<int,set<int>>::iterator it;
set<int>::iterator sit;
set<int>::iterator tmp;
int main(){
    fastio;
    int n,k;
    cin >> n >> k;
    string s;
    cin >> s;
    unordered_map<int,set<int>> ad;
    unordered_map<int,set<int>> bc;
    pi pos;
    rep(i,n){
      int tx,ty;
      cin >> tx >> ty;
      // (x,y) 를 45도 만큼 시계 방향으로 돌리면
      int x,y;
      x = tx+ty;
      y = tx- ty;
      if(i == 0) pos = {x,y};

      it = ad.find(y);
      if(it == ad.end()){
        set<int> si;
        si.insert(x);
        ad.insert(pair<int,set<int>>(y, si));
      }
      else
        it->second.insert(x);
      
      it = bc.find(x);
      if(it == bc.end()){
        set<int> si;
        si.insert(y);
        bc.insert(pair<int,set<int>>(x,si));
      }
      else
        it->second.insert(y);
    }
    rep(i,k){
      set<int> & v = ((s[i]=='A' || s[i] =='D') ? ad[pos.second] : bc[pos.first]);
      set<int> & vv = ((s[i]=='A' || s[i] =='D') ? bc[pos.first] : ad[pos.second]);
      if(v.size() == 1) continue;
      int key = ((s[i]=='A' || s[i] =='D') ? pos.first : pos.second);
      int nkey = ((s[i]=='A' || s[i] =='D') ? pos.second : pos.first);
      sit = v.lower_bound(key);
      tmp = sit;
      if(s[i] == 'A' || s[i] == 'B'){
        ++sit;
        if(sit == v.end()) continue;
      }
      else{
        if(sit == v.begin()) continue;
        --sit;
      }
      if(s[i] == 'A' || s[i] == 'D') pos.first = *sit;
      else pos.second = *sit;

      v.erase(tmp);
      vv.erase(nkey);
    }
    cout << (pos.first+pos.second)/2 << ' ' << (pos.first - pos.second)/2;
    return 0;
}