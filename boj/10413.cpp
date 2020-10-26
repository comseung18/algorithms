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

// �� ���̻���� ù t���ڸ� �������� �� �׷��ȣ�� �־��� ��,
// �־��� �� ���̻縦 ù 2*t ���ڸ� �������� ���Ѵ�.
// group[] �� ���̰� 0�� ���̻絵 �����Ѵ�.
struct Comparator{
    const vector<int>& group;
    int t;
    Comparator(const vector<int> &_group, int _t):
    group(_group), t(_t) {}

    bool operator() (int a, int b){
        // ù t ���ڰ� �ٸ��� �̵��� �̿��� ���Ѵ�.
        if(group[a] != group[b]) return group[a] < group[b];

        // �ƴ϶�� S[a+t..] �� S[b+t..]�� ù t���ڸ� ���Ѵ�.
        return group[a+t] < group[b+t];
    }
};

// s�� ���̻� �迭�� ����Ѵ�.
vector<int> getSuffixArray(const string& s){
    int n = s.size();
    // group[i]=���̻���� ù t���ڸ� �������� �������� ��,
    // s[i..] �� ���� �׷��� ��ȣ
    // t =1 �� ���� ������ �� ���� s[i..]�� ù ���ڷ� �׷� ��ȣ��
    // ���� �൵ ���� ȿ���� �ִ�.
    int t = 1;
    vector<int> group(n+1);
    for(int i=0;i<n;++i) group[i] = s[i];
    group[n] = -1;
    // ��������� ���̻� �迭�� �� ��ȯ ��. �� �迭�� lg(n)�� �����Ѵ�.
    vector<int> perm(n);
    for(int i=0;i<n;++i) perm[i] = i;
    while(t<n){
        // group[]�� ù t���ڸ� �������� ����� �״�.
        // ù 2t ���ڸ� �������� perm�� �ٽ� �����Ѵ�.
        Comparator compareUsing2T(group, t);
        sort(perm.begin(), perm.end(), compareUsing2T);
        // 2t ���ڰ� n�� �Ѵ´ٸ� ���� ���̻� �迭 �ϼ�!
        t *= 2;
        if(t >= n) break;
        // 2t ���ڸ� �������� �� �׷� ������ �����
        vector<int> newGroup(n+1);
        newGroup[n] = -1;
        newGroup[perm[0]] = 0;
        for(int i=1;i<n;++i)
            if(compareUsing2T(perm[i-1],perm[i]))
                newGroup[perm[i]] = newGroup[perm[i-1]] +1;
            else
                newGroup[perm[i]] = newGroup[perm[i-1]];
        group = newGroup;
    }
    return perm;
}

// SA �� s �� suffixArray �� ��,
// LCP Array �� ��ȯ��.
// lcp[k] = lcp(k-1,k)
// lcp[0] �� ���ǵ��� ����.
vector<int> getLCPArray(const string& s, const vector<int>& sa){
    int n = s.size();

    // rank �迭���� ���̻� �迭 ������ ����.
    vector<int> rank(n);
    for(int i=0;i <n; ++i ) rank[sa[i]] = i;

    int len = 0;
    vector<int> lcp(n);

    for(int i=0;i<n;i++){
        int k = rank[i];
        if(k){
            int j = sa[k-1];
            while(s[j+len] == s[i + len]) ++len;
            lcp[k] = len;

            if(len) --len;
        }
    }
    return lcp;
}

int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
        string s;
        cin >> s;
        vi sa = getSuffixArray(s);
        vi lcp = getLCPArray(s,sa);

        int ans = 0;
        int n = s.size();

        for(int i=0;i<n;i++){
            int cp =0;
            if(i > 1) cp = (lcp[i] >lcp[i-1]? 
            lcp[i]-lcp[i-1] : 0);
            else cp = lcp[i];
            ans += cp;
        }
        cout << ans << endl;
    }
    return 0;
}
