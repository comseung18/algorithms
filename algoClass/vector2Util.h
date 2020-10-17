#include <./vector2.h>

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

typedef vector<vector2> polygon;

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

// 반시계 방향으로 주어진
// 두 "볼록" 다각형의 겹쳐진 부분의 넓이를 구한다.
// 이 때 각 볼록 다각형의 꼭짓점은 다른 볼록 다각형의
// 변 위에 없다고 가정한다.
double polygonIntersection(const polygon& p, const polygon& q){
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
