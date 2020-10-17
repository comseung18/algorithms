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
const double EPSILON = 1e-9;

typedef vector<vector2> polygon;
// 그라함스캔을 이용해 convexHull 을 찾음
// points 의 vector 가 sorting 되므로 변경됨을 주의!
polygon grahamScan(vector<vector2>& points){
    // y 좌표가 가장 낮은 점을 선택
    // 그러한 점이 여러개 라면 x 가 가장 낮은 점 선택
    sort(points.begin(),points.end(),
    [](const vector2& v1, const vector2& v2){
        return v1.y != v2.y ? v1.y < v2.y : v1.x < v2.x;
    });

    vector2 pivot = points[0];
    // x 축 pivot 과 이루는 각이 작은 순서로 정렬
    sort(points.begin()+1, points.end(),
    [pivot](const vector2& v1, const vector2& v2){
        
        double tmp = ccw(pivot,v2,v1);
        if(abs(tmp) > EPSILON) return tmp < 0;
        return (pivot-v1).norm() < (pivot-v2).norm();
    });
    stack<int> s;
    s.push(0);
    s.push(1);

    int n = points.size();
    int next = 2;
    while(next < n){
        while(s.size() >= 2){
            int first, second;
            second = s.top(); s.pop();
            first = s.top();

            if(ccw(points[first],points[second],
            points[next]) > 0){
                s.push(second);
                break;
            }
        }
        s.push(next++);
    }
    
    polygon p;
    while(!s.empty()){
        p.push_back(points[s.top()]);
        s.pop();
    }
    return p;
}

// 시계 반대 방향으로 주어진 블록 다각형에서 가장 먼 꼭짓점 쌍 사이의 거리를 반환한다.
double diameter(const polygon& p){
    int n = p.size();
    // 우선 가장 왼쪽에 있는 점과 오른쪽에 있는 점을 찾는다.
    int left = min_element(p.begin(),p.end()) - p.begin();
    int right = max_element(p.begin(), p.end()) - p.begin();

    //p[left] 와 p[right] 에 각각 수직선을 붙인다. 두 수직선은 서로 정반대 방향을 가리키므로,
    // A의 방향만을 표현하면된다. 
    vector2 calipersA(0,1);
    double ret = (p[right]-p[left]).norm();

    // toNext[i] = p[i]에서 다음 점까지의 방향을 나타내는 단위 벡터
    vector<vector2> toNext(n);
    for(int i=0;i<n;++i)
        toNext[i] = (p[(i+1)%n] - p[i]).normalize();
    
    int a = left, b = right;

    // 반 바퀴 돌아서 두 선분이 서로 위치를 바꿀 때까지 계속한다.
    while(a!= right || b != left){
        // a에서 다음 점까지의 각도와 b에서 다음 점까지의 각도 중 어느 쪽이 작은지 확인
        double cosA = calipersA.dot(toNext[a]);
        double cosB = -calipersA.dot(toNext[b]);
        if(cosA > cosB){
            calipersA = toNext[a];
            a = (a+1)%n;
        }
        else{
            calipersA = -toNext[b];
            b = (b+1)%n;
        }
        ret = max(ret, (p[a]-p[b]).norm());
    }
    return ret;
}

int main(){
    //fastio;
    int N;
    cin >> N;
    vector<vector2> v;
    rep(i,N){
        int x,y;
        cin >> x >> y;
        v.push_back(vector2(x,y));
    }
    polygon p = grahamScan(v);
    printf("%.7f",diameter(p));
    return 0;
}