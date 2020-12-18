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

struct Query{
    char q;
    int k,x;
    Query(){
        q = 'F';
        k = 0;
        x = 0;
    }
    Query(char q, int k, int x=0):
    q(q), k(k),x(x){}

};
vi mySolve(int n, const vi& v, int m, const vector<Query>& qs){
    vi ans;
    vi t(n+1,0);
    set<int> s;
    rep(i,m){
        char q;
        int k,x;
        q = qs[i].q;
        if(q== 'F'){
            k = qs[i].k;
            x = qs[i].x;
            auto sit = s.lower_bound(-k);
            if(sit != s.end() && t[-(*sit)] >= x) continue;

            sit = s.find(-k);
            if(sit == s.end()) s.insert(-k);

            t[k] = max(t[k],x);
            
            auto it = s.begin();
            sit = s.find(-k);
            while(it != s.end() && it != sit){
                if(t[-(*it)] <= t[k]) it = s.erase(it);
                else break;
            }
        }else{
            k = qs[i].k;
            auto it = s.lower_bound(-k);
            if(it == s.end()) ans.push_back(v[k]);
            else ans.push_back(max(t[-(*it)],v[k]));
        }
    }
    return ans;
}

vi correct(int n, const vi& v, int m, const vector<Query>& qs){
    vi ans;
    vi t = v;
    rep(i,m){
        char q;
        int k,x;
        q = qs[i].q;
        if(q== 'F'){
            k = qs[i].k;
            x = qs[i].x;
            for(int j=k;j<=n;++j) t[j] = max(t[j],x);
        }else if(q=='Q'){
            k = qs[i].k;
            ans.push_back(t[k]);
        }
    }
    return ans;
}

bool comp(const vi& v1, const vi& v2){
    if(v1.size() != v2.size()) return false;
    rep(i,v1.size()) if(v1[i] != v2[i]) return false;
    return true;
}
int main(){
    fastio;
    srand((unsigned int)time(0));
    for(int n=1;n<=10;++n){
        vi v(n+1);
        rep(i,n) v[i+1] = min(1000000000,rand()+1);
        int m = rand()%100 +1;
        vector<Query> qs;
        rep(i,m){
            char q = (rand()%2? 'F' :'Q');
            int k,x;
            if(q== 'F'){
                k = rand()%n+1;
                x = min(rand()+1,1000000000);
            }else{
                k = rand()%n+1;
            }
            qs.push_back(Query(q,k,x));
        }
        vi my = mySolve(n,v,m,qs);
        vi cor = correct(n,v,m,qs);
        if(!comp(my,cor)){
            cout << "틀렸음\n";
            cout << "너의 정답 : ";
            rep(i,my.size()) cout << my[i] << ' ';
            cout << endl;
            cout << "옳은 정답 : ";
            rep(i,cor.size()) cout << cor[i] << ' ';
            cout << endl;
            cout << "입력 :";
            cout << n << endl;
            rep(i,n) cout << v[i+1] << ' ';
            cout << endl;
            cout << m << endl;
            rep(i, qs.size()){
                cout << qs[i].q << ' ' << qs[i].k << ' ' << qs[i].x << endl;
            }
            cout << "=================\n";
        }
        cout << "테스트 종료\n";
    }
    return 0;
}