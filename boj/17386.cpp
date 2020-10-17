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

int main(){
    fastio;
    vector2 v[4];
    rep(i,4){
        int x,y;
        cin >> x >> y;
        v[i] = vector2(x,y);
    }
    cout << (int)segmentIntersects(v[0],v[1],
    v[2],v[3]);

    return 0;
}