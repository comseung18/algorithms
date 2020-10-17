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
    ll x,y;

    explicit vector2(ll _x=0, ll _y=0):
    x(_x),y(_y) {
        
    }

    bool operator==(const vector2& rhs) const{
        return x== rhs.x && y == rhs.y;
    }

    bool operator <(const vector2& rhs) const{
        return x != rhs.x ? x < rhs.x : y <rhs.y;
    }
    bool operator <=(const vector2& rhs) const{
        if(*this == rhs) return true;
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

    ll cross(const vector2& rhs) const{
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
ll ccw(vector2 a, vector2 b){
    return a.cross(b);
}

// 점 p 를 기준으로 벡터 b가 벡터 a의 반시계 방향이면 음수,
// 시계 방향이면 음수, 평행이면 0 을 반환

ll ccw(vector2 p, vector2 a, vector2 b){
    
    ll res = ccw(a-p,b-p);
    if(res >0) return 1;
    if( res<0) return -1;
    if(res == 0) return 0;
}
// p 가 (a,b) 를 감싸면서 각 변이 x,y 축에 평행한 최소 사각형 내부에 있는지 확인한다.
// a,b,p 는 일직선 안에 있다고 가정한다.
bool inBoundingRectangle(vector2 p, vector2 a, vector2 b){
    if(b<a) swap(a,b);
    return p==a || p==b || 
    (((a<=p) && (p<=b)) && (min(a.y,b.y)<= p.y &&
    p.y <= max(a.y,b.y) ));
}

// 두 선분이 서로 접촉하는지 여부를 반환한다.
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d){
    ll ab = ccw(a,b,c)*ccw(a,b,d);
    ll cd = ccw(c,d,a)*ccw(c,d,b);

    // 두 선분이 한 직선 위에 있거나 끝점이 곂치는 경우
    if(ab== 0 && cd == 0){
        if(b<a) swap(a,b);
        if(d<c) swap(c,d);
        return !(b<c || d<a);
    }
    return ab <= 0 && cd <= 0;
}

void vector2_cin(vector2 &v){
    cin >> v.x >> v.y;
}
int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
        vector2 a,b,r1,r3;
        vector2_cin(a);
        vector2_cin(b);
        vector2_cin(r1);
        vector2_cin(r3);

        vector2 r2,r4;
        if(b<a) swap(a,b);
        if(r3 < r1) swap(r1,r3);
        r2 = vector2(r1.x + r3.x - r1.x,r1.y);
        r4 = vector2(r1.x, r1.y + r3.y - r1.y);
        bool ans = segmentIntersects(a,b,r1,r2) ||
        segmentIntersects(a,b,r2,r3) ||
        segmentIntersects(a,b,r3,r4) ||
        segmentIntersects(a,b,r4,r1);
        if(ans || (
            inBoundingRectangle(a,r1,r3) || 
            inBoundingRectangle(b,r1,r3)
        )) cout << 'T' << endl;
        else cout << 'F' << endl;
    }
    return 0;
}