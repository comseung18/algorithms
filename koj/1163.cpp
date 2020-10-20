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

int n;
vi v;
vi seg;

// segment 의 num 노드가 [left,right] 를 담당할 때
// v[left~right] 까지 xor 한 결과를 return

int seg_init(int num, int left, int right){
    if(left == right) return seg[num] = v[left];
    int mid = (left+right)/2;
    return seg[num] = seg_init(num*2,left,mid)^seg_init(num*2+1,mid+1,right);
}

// v[index] 를 val 과 xor 한 결과를 segment 에 반영
int seg_update(int num, int left, int right, int index, int val){
    if(left > index || right < index) return seg[num];
    if(left == right) return seg[num]^= val;

    int mid = (left+right)/2;
    return seg[num] = seg_update(num*2,left,mid,index,val)^seg_update(num*2+1,mid+1,right,index,val);
}

int seg_query(int num, int left, int right, int ql, int qr){
    if(left > qr || right < ql) return 0;
    if(ql <= left && right <= qr) return seg[num];

    int mid = (left+right)/2;
    return seg_query(num*2,left,mid,ql,qr)^seg_query(num*2+1,mid+1,right,ql,qr);
}
int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
        cin >> n;
        v = vi(n);
        seg = vi(5*n);

        rep(i,n) cin >> v[i];
        seg_init(1,0,n-1);
        int m;
        cin >> m;
        rep(i,m){
            int a,b,c;
            cin >> a >> b >> c;
            if(a==1){
                seg_update(1,0,n-1,b,c);
            }else{
                cout << seg_query(1,0,n-1,b,c) << endl;
            }
        }
    }
    return 0;
}