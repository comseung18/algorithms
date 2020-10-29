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
    map<int, multiset<int>> m;
    int n;
    cin >> n;
    rep(i,n){
        int l,h,r;
        cin >> l >> h >> r;
        m[l].insert(h);
        m[r].insert(-h);
    }
    int height = 0;
    multiset<int> heights;
    heights.insert(0);
    for(auto it = m.begin();it != m.end(); ++it){
        int x = it->first;
        int y = *(it->second.rbegin());

        // 상승이벤트들을 기록과 하강 이벤트 삭제
        for(auto sit = it->second.begin(); sit != it->second.end(); ++sit){
            if(*sit > 0)
                heights.insert(*sit);
            else
                heights.erase(-(*sit));
        }

        // 상승 이벤트이면
        if(y > 0){
            // 높이가 변했으므로.
            if(y > height){
                height = y;
                cout << x << ' '
                << height << ' ';
            }
        }
        // 하강 이벤트이면
        else{
            if(height != *heights.rbegin()){
                height = *heights.rbegin();
                cout << x << ' '
                << height << ' ';
            }
        }
    }
    return 0;
}