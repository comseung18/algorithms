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

typedef vector<vector2> polygon;

const double EPSILON = 1e-9;
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

// (a,b) 를 포함하는 선과 (c,d) 를 포함하는 선의 교점을 x 에 반환한다.
// 두 선이 평행이면 (곂치는 경우를 포함) 거짓을, 아니면 참을 반환한다.
bool lineIntersection(vector2 a, vector2 b,
vector2 c, vector2 d, vector2& x){
    double det = (b-a).cross(d-c);

    // 두 선이 평행인 경우
    if(fabs(det)  < EPSILON) return false;
    x = a + (b-a)*((c-a).cross(d-c)/det);
    return true;
}

// (a,b)와 (c,d)가 평행한 두 선분일 때 
// 이들이 한 점에서 곂치는 지 확인하다
bool parallelSegments(vector2 a, vector2 b,
vector2 c, vector2 d, vector2 &p){
    if(b < a) swap(a,b);
    if(d<c) swap(c,d);
    // 한 직선 위에 없거나 두 선분이 겹치지 않는 경우를 우선 걸러낸다.
    if(ccw(a,b,c) != 0 || b <c || d < a) return false;
    
    if(a<c) p =c; else p=a;
    return true;
}

// p 가 (a,b) 를 감싸면서 각 변이 x,y 축에 평행한 최소 사각형 내부에 있는지 확인한다.
// a,b,p 는 일직선 안에 있다고 가정한다.
bool inBoundingRectangle(vector2 p, vector2 a, vector2 b){
    if(b<a) swap(a,b);
    return p==a || p==b || (a<p) && (p<b);
}

// (a,b) 선분과 (c,d) 선분의 교점을 p 에 반환한다.
// 교점이 여러 개일 경우 아무 점이나 반환한다.
// 두 선분이 교차하지 않을 경우 false 를 반환한다.
bool segmentIntersection(vector2 a, vector2 b,
vector2 c, vector2 d, vector2&p){

    // 두 직선이 평행인 경우를 우선 예외로 처리한다.
    if(!lineIntersection(a,b,c,d,p))
        return parallelSegments(a,b,c,d,p);
    
    // p 가 두 선분에 포함되어 있는 경우에만 참을 반환한다.
    return inBoundingRectangle(p,a,b) &&
    inBoundingRectangle(p,c,d);
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

// 주어진 단순 다각형 p의 넓이를 구한다.
// p는 각 꼭지점의 위치 벡터의 집합으로 주어진다.
double area(const polygon& p){
    double ret = 0;
    for(int i=0;i<p.size();++i){
        int j = (i+1)%p.size();
        ret += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return fabs(ret)/2.0;
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


// 반시계 방향으로 주어진
// 두 "볼록" 다각형의 겹쳐진 부분의 넓이를 구한다.
// 이 때 각 볼록 다각형의 꼭짓점은 다른 볼록 다각형의
// 변 위에 없다고 가정한다.
double polygonIntersectionArea(const polygon& p, const polygon& q){
    // 서로 닿지 않는 경우를 예외처리
    if(!polygonIntersects(p,q)) return 0;

    // 겹쳐진 볼록 다각형은 
    // p 안에 있는 q 의 꼭짓점
    // q 안에 있는 p 의 꼭짓점
    // p와 q 의 선분의 교점들
    // 을 이용하여 만들어진다.
    vector<vector2> v;
    int n = p.size();
    int m = q.size();
    for(int i=0;i<n;++i)
        if(isInside(p[i],q)) v.push_back(p[i]);
    for(int i=0;i<m;++i)
        if(isInside(q[i],p)) v.push_back(q[i]);
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j){
            vector2 x;
            if(segmentIntersection(p[i],p[(i+1)%n],
            q[j],q[(j+1)%m],x)){
                v.push_back(x);
            }
        }

    // v의 점들을 이용해 컨백스홀을 구성한다.
    polygon c = giftWrap(v);
    // c 의 넓이를 구한다.
    return area(c);
            
}

int main(){
    //fastio;
    int n,m;
    cin >> n >> m;
    polygon p1,p2;
    rep(i,n){
        int x,y;
        cin >> x >> y;
        p1.push_back(vector2(x,y));
    }
    rep(i,m){
        int x,y;
        cin >> x >> y;
        p2.push_back(vector2(x,y));
    }
    double ans = polygonIntersectionArea(p1,p2);
    printf("%.9f",ans);
    return 0;
}