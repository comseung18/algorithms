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

typedef vector<vector2> polygon;

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

// points 에 있는 점들을 모두 포함하는 최소의 볼록 다각형을 찾는다.
polygon giftWrap(const vector<vector2> & points){
    int n = points.size();
    polygon hull;

    vector2 pivot = *min_element(points.begin(),points.end(),
    [](const vector2& v1, const vector2& v2){
        return v1.y != v2.y ? v1.y > v2.y :
        v1.x < v2.x;
    });
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

int main(){
    fastio;
    int T;
    cin >> T;
    while(T--){
        int N;
        cin >> N;
        vector<vector2> v;
        rep(i,N){
            int x,y;
            cin >> x >> y;
            v.push_back(vector2(x,y));
        }
        polygon p = giftWrap(v);
        cout << p.size() << endl;
        rep(i,p.size()){
            cout << (int)p[i].x << ' ' << (int)p[i].y << endl;
        }

    }
    return 0;
}