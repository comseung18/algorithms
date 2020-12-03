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
class vector2{
    public:
    static const double PI;
    double x,y;
    int num;
    explicit vector2(double _x=0, double _y=0, int _num = 0):
    x(_x),y(_y),num(_num) {
        
    }

    bool operator==(const vector2& rhs) const{
        return x== rhs.x && y == rhs.y;
    }

    bool operator <(const vector2& rhs) const{
        return x != rhs.x ? x < rhs.x : y <rhs.y;
    }

    vector2 operator+(const vector2& rhs) const{
        return vector2(x+rhs.x, y+rhs.y);
    }
    vector2 operator-(const vector2& rhs) const{
        return vector2(x-rhs.x, y-rhs.y);
    }
    vector2 operator-()const{
        return vector2(-x,-y);
    }

    vector2 operator*(double rhs) const{
        return vector2(x*rhs,y*rhs);
    }

    double norm() const{
        return hypot(x,y);
    }

    vector2 normalize() const{
        return vector2(x/norm(), y/norm());
    }

    double polar() const{
        return fmod(atan2(y,x) + 2*PI, 2*PI);
    }
    double dot(const vector2& rhs) const{
        return x*rhs.x + y*rhs.y;
    }

    double cross(const vector2& rhs) const{
        return x*rhs.y - rhs.x*y;
    }

    vector2 project(const vector2& rhs) const{
        vector2 r = rhs.normalize();
        return r*r.dot(*this);
    }
};

const double vector2::PI = 2.0*acos(0.0);
typedef vector<vector2> polygon;

double ccw(vector2 a, vector2 b){
    return a.cross(b);
}

double ccw(vector2 p, vector2 a, vector2 b){
    return ccw(a-p,b-p);
}

vi used;

polygon giftWrap(const vector<vector2> & points,int t){
    int n = points.size();
    polygon hull;

    vector2 pivot = *min_element(points.begin(),points.end());
    hull.push_back(pivot);
    used[pivot.num] = t;
    while(1){
        vector2 ph = hull.back(), next = points[0];
        for(int i=1;i<n;++i){
            double cross = ccw(ph, next, points[i]);
            double dist = (next - ph).norm()
            - (points[i]-ph).norm();
            if(cross > 0 || (cross==0 && dist < 0))
                next = points[i];
        }
        if(next == pivot) break;
        hull.push_back(next);
        used[next.num] = t;
    }
    return hull;
}

double area(const polygon& p){
    double ret = 0;
    for(int i=0;i<p.size();++i){
        int j = (i+1)%p.size();
        ret += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return fabs(ret)/2.0;
}

const double EPSILON = 1e-9;

int main(){
    fastio;
    int n;
    cin >> n;
    used = vi(n,0);
    vector< vector2 > v;
    rep(i,n){
        int x,y;
        cin >> x >> y;
        v.push_back(vector2(x,y,i));
    }
    int f = 1; // 층
    while(1){
        // 만든 층의 넓이가 0이면 종료
        vector< vector2 > t;
        rep(i,v.size()) if(used[v[i].num] == 0) t.push_back(v[i]);
        if(t.size() <= 2) break;
        polygon p = giftWrap(t,f);
        if(area(p) < EPSILON){
            rep(i,t.size()) used[t[i].num] = 0;
            break;
        }
        ++f;
    }
    rep(i,n) cout << used[i] << ' ';
    return 0;
}