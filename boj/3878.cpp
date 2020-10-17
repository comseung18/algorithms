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

    explicit vector2(double _x=0, double _y=0):
    x(_x),y(_y) {
        
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

// 원점에서 벡터 b가 벡터 a의 반시계 방향이면 양수,
// 시계방향이면 음수, 평행이면 0을 반환
double ccw(vector2 a, vector2 b){
    return a.cross(b);
}

// 점 p 를 기준으로 벡터 b가 벡터 a의 반시계 방향이면 음수,
// 시계 방향이면 음수, 평행이면 0 을 반환

double ccw(vector2 p, vector2 a, vector2 b){
    return ccw(a-p,b-p);
}

typedef vector<vector2> polygon;

// points 에 있는 점들을 모두 포함하는 최소의 볼록 다각형을 찾는다.
polygon giftWrap(const vector<vector2> & points){
    int n = points.size();
    polygon hull;

    vector2 pivot = *min_element(points.begin(),points.end());
    hull.push_back(pivot);
    while(1){
        //ph 에서 시작하는 벡터가 가장 왼쪽인 점 next 를 찾는다.
        //평행인 점이 여러 개 있으면 가장 먼 것을 선택한다.
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
    }
    return hull;
}

// 점 q가 다각형 p 안에 포함되어 있을 경우 참, 아닌 경우
// 거짓을 반환한다. q가 다각형의 경계 위에 있는 경우의
// 반환 값은 정의되어 있지 않다.
bool isInside(vector2 q, const vector<vector2>&p){
    int crosses = 0;
    for(int i=0;i<p.size();++i){
        int j =(i+1)%p.size();
        // (p[i],p[j])가 반직선을 세로로 가로지르는가?
        if((p[i].y > q.y) != (p[j].y > q.y)){
            double atX = (p[j].x - p[i].x)*(q.y - p[i].y)/
            (p[j].y - p[i].y) + p[i].x;
            if(q.x < atX) ++crosses;
        }
    }
    return crosses%2 > 0;
}

// 두 선분이 서로 접촉하는지 여부를 반환한다.
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d){
    double ab = ccw(a,b,c)*ccw(a,b,d);
    double cd = ccw(c,d,a)*ccw(c,d,b);

    // 두 선분이 한 직선 위에 있거나 끝점이 곂치는 경우
    if(ab== 0 && cd == 0){
        if(b<a) swap(a,b);
        if(d<c) swap(c,d);
        return !(b<c || d<a);
    }
    return ab <= 0 && cd <= 0;
}

// 두 다각형이 서로 닿거나 곂치는지 여부를 반환한다.
// 한 점이라도 곂친다면 true를 반환한다.
bool polygonIntersects(const polygon& p, const polygon& q){
    int n = p.size(), m= q.size();
    // 우선 한 다각형이 다른 다각형에 포함되어 있는 경우를
    // 확인하자.
    if(isInside(p[0],q) || isInside(q[0],p)) return true;

    // 이 외의 경우, 두 다각형이 서로 곂친다면 서로 닿는 두변이
    // 반드시 존재한다.
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            if(segmentIntersects(p[i],p[(i+1)%n],
            q[j],q[(j+1)%m])) return true;
    return false;
}


int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
        int n,m;
        cin >> n >> m;
        vector<vector2> p,q;
        rep(i,n){
            int x,y;
            cin >> x >> y;
            p.push_back(vector2(x,y));
        }
        rep(i,m){
            int x,y;
            cin >> x >> y;
            q.push_back(vector2(x,y));
        }
        polygon p1 = giftWrap(p);
        polygon p2 = giftWrap(q);
        if(polygonIntersects(p1,p2)) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
    return 0;
}