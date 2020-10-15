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
vi inorder,postorder;
vi idx_inorder;
void preorder(int le, int ri, int pivot = -1){
    if(le > ri) return;
    int v = postorder[ri];
    cout << v << ' ';
    if(le >= ri) return;
    int idx = idx_inorder[v];
    int sz = idx - pivot -1;
    preorder(le,le+sz-1,pivot);
    preorder(le+sz,ri-1,idx);
}
int main(){
    fastio;
    cin >> n;
    inorder = vi(n);
    postorder = vi(n);
    idx_inorder = vi(n+1);
    rep(i,n){
        cin >> inorder[i];
        idx_inorder[inorder[i]] = i;
    } 
    rep(i,n) cin >> postorder[i];
    preorder(0,n-1);
    return 0;
}
