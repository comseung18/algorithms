#include <./vector2.h>

const double EPSILON = 1e-9;
// ?��?��?��?�� 벡터 b�? 벡터 a?�� 반시�? 방향?���? ?��?��,
// ?��계방?��?���? ?��?��, ?��?��?���? 0?�� 반환
double ccw(vector2 a, vector2 b){
    return a.cross(b);
}

// ?�� p �? 기�???���? 벡터 b�? 벡터 a?�� 반시�? 방향?���? ?��?��,
// ?���? 방향?���? ?��?��, ?��?��?���? 0 ?�� 반환

double ccw(vector2 p, vector2 a, vector2 b){
    return ccw(a-p,b-p);
}

// (a,b) �? ?��?��?��?�� ?���? (c,d) �? ?��?��?��?�� ?��?�� 교점?�� x ?�� 반환?��?��.
// ?�� ?��?�� ?��?��?���? (곂치?�� 경우�? ?��?��) 거짓?��, ?��?���? 참을 반환?��?��.
bool lineIntersection(vector2 a, vector2 b,
vector2 c, vector2 d, vector2& x){
    double det = (b-a).cross(d-c);

    // ?�� ?��?�� ?��?��?�� 경우
    if(fabs(det)  < EPSILON) return false;
    x = a + (b-a)*((c-a).cross(d-c)/det);
    return true;
}

// (a,b)??? (c,d)�? ?��?��?�� ?�� ?��분일 ?�� 
// ?��?��?�� ?�� ?��?��?�� 곂치?�� �? ?��?��?��?��
bool parallelSegments(vector2 a, vector2 b,
vector2 c, vector2 d, vector2 &p){
    if(b < a) swap(a,b);
    if(d<c) swap(c,d);
    // ?�� 직선 ?��?�� ?��거나 ?�� ?��분이 겹치�? ?��?�� 경우�? ?��?�� 걸러?��?��.
    if(ccw(a,b,c) != 0 || b <c || d < a) return false;
    
    if(a<c) p =c; else p=a;
    return true;
}

// p �? (a,b) �? 감싸면서 �? �??�� x,y 축에 ?��?��?�� 최소 ?��각형 ?���??�� ?��?���? ?��?��?��?��.
// a,b,p ?�� ?��직선 ?��?�� ?��?���? �??��?��?��.
bool inBoundingRectangle(vector2 p, vector2 a, vector2 b){
    if(b<a) swap(a,b);
    return p==a || p==b || (a<p) && (p<b);
}

// (a,b) ?��분과 (c,d) ?��분의 교점?�� p ?�� 반환?��?��.
// 교점?�� ?��?�� 개일 경우 ?���? ?��?��?�� 반환?��?��.
// ?�� ?��분이 교차?���? ?��?�� 경우 false �? 반환?��?��.
bool segmentIntersection(vector2 a, vector2 b,
vector2 c, vector2 d, vector2&p){

    // ?�� 직선?�� ?��?��?�� 경우�? ?��?�� ?��?���? 처리?��?��.
    if(!lineIntersection(a,b,c,d,p))
        return parallelSegments(a,b,c,d,p);
    
    // p �? ?�� ?��분에 ?��?��?��?�� ?��?�� 경우?���? 참을 반환?��?��.
    return inBoundingRectangle(p,a,b) &&
    inBoundingRectangle(p,c,d);
}

// ?�� ?��분이 ?���? ?��촉하?���? ?���?�? 반환?��?��.
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d){
    double ab = ccw(a,b,c)*ccw(a,b,d);
    double cd = ccw(c,d,a)*ccw(c,d,b);

    // ?�� ?��분이 ?�� 직선 ?��?�� ?��거나 ?��?��?�� 곂치?�� 경우
    if(ab== 0 && cd == 0){
        if(b<a) swap(a,b);
        if(d<c) swap(c,d);
        return !(b<c || d<a);
    }
    return ab <= 0 && cd <= 0;
}

// ?�� q�? ?��각형 p ?��?�� ?��?��?��?�� ?��?�� 경우 �?, ?��?�� 경우
// 거짓?�� 반환?��?��. q�? ?��각형?�� 경계 ?��?�� ?��?�� 경우?��
// 반환 값�?? ?��?��?��?�� ?���? ?��?��.
bool isInside(vector2 q, const vector<vector2>&p){
    int crosses = 0;
    for(int i=0;i<p.size();++i){
        int j =(i+1)%p.size();
        // (p[i],p[j])�? 반직?��?�� ?��로로 �?로�??르는�??
        if((p[i].y > q.y) != (p[j].y > q.y)){
            double atX = (p[j].x - p[i].x)*(q.y - p[i].y)/
            (p[j].y - p[i].y) + p[i].x;
            if(q.x < atX) ++crosses;
        }
    }
    return crosses%2 > 0;
}

typedef vector<vector2> polygon;

// 주어�? ?��?�� ?��각형 p?�� ?��?���? 구한?��.
// p?�� �? �?�??��?�� ?���? 벡터?�� 집합?���? 주어진다.
double area(const polygon& p){
    double ret = 0;
    for(int i=0;i<p.size();++i){
        int j = (i+1)%p.size();
        ret += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return fabs(ret)/2.0;
}
// points ?�� ?��?�� ?��?��?�� 모두 ?��?��?��?�� 최소?�� 볼록 ?��각형?�� 찾는?��.
polygon giftWrap(const vector<vector2> & points){
    int n = points.size();
    polygon hull;

    vector2 pivot = *min_element(points.begin(),points.end());
    hull.push_back(pivot);
    while(1){
        //ph ?��?�� ?��?��?��?�� 벡터�? �??�� ?��쪽인 ?�� next �? 찾는?��.
        //?��?��?�� ?��?�� ?��?�� �? ?��?���? �??�� �? 것을 ?��?��?��?��.
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

// ?�� ?��각형?�� ?���? ?��거나 곂치?���? ?���?�? 반환?��?��.
// ?�� ?��?��?��?�� 곂친?���? true�? 반환?��?��.
bool polygonIntersects(const polygon& p, const polygon& q){
    int n = p.size(), m= q.size();
    // ?��?�� ?�� ?��각형?�� ?���? ?��각형?�� ?��?��?��?�� ?��?�� 경우�?
    // ?��?��?��?��.
    if(isInside(p[0],q) || isInside(q[0],p)) return true;

    // ?�� ?��?�� 경우, ?�� ?��각형?�� ?���? 곂친?���? ?���? ?��?�� ?���??��
    // 반드?�� 존재?��?��.
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            if(segmentIntersects(p[i],p[(i+1)%n],
            q[j],q[(j+1)%m])) return true;
    return false;
}

// 반시�? 방향?���? 주어�?
// ?�� "볼록" ?��각형?�� 겹쳐�? �?분의 ?��?���? 구한?��.
// ?�� ?�� �? 볼록 ?��각형?�� �?짓점??? ?���? 볼록 ?��각형?��
// �? ?��?�� ?��?���? �??��?��?��.
double polygonIntersection(const polygon& p, const polygon& q){
    // ?���? ?���? ?��?�� 경우�? ?��?��처리
    if(!polygonIntersects(p,q)) return 0;

    // 겹쳐�? 볼록 ?��각형??? 
    // p ?��?�� ?��?�� q ?�� �?짓점
    // q ?��?�� ?��?�� p ?�� �?짓점
    // p??? q ?�� ?��분의 교점?��
    // ?�� ?��?��?��?�� 만들?��진다.
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

    // v?�� ?��?��?�� ?��?��?�� 컨백?��????�� 구성?��?��.
    polygon c = giftWrap(v);
    // c ?�� ?��?���? 구한?��.
    return area(c);
            
}

// 그라?��?��캔을 ?��?��?�� convexHull ?�� 찾음
// points ?�� vector �? sorting ?���?�? �?경됨?�� 주의!
polygon grahamScan(vector<vector2>& points){
    // y 좌표�? �??�� ?��??? ?��?�� ?��?��
    // 그러?�� ?��?�� ?��?���? ?���? x �? �??�� ?��??? ?�� ?��?��
    sort(points.begin(),points.end(),
    [](const vector2& v1, const vector2& v2){
        return v1.y != v2.y ? v1.y < v2.y : v1.x < v2.x;
    });

    vector2 pivot = points[0];
    // x �? pivot �? ?��루는 각이 ?��??? ?��?���? ?��?��
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

// ?���? 반�?? 방향?���? 주어�? 블록 ?��각형?��?�� �??�� �? �?짓점 ?�� ?��?��?�� 거리�? 반환?��?��.
double diameter(const polygon& p){
    int n = p.size();
    // ?��?�� �??�� ?��쪽에 ?��?�� ?���? ?��른쪽?�� ?��?�� ?��?�� 찾는?��.
    int left = min_element(p.begin(),p.end()) - p.begin();
    int right = max_element(p.begin(), p.end()) - p.begin();

    //p[left] ??? p[right] ?�� 각각 ?��직선?�� 붙인?��. ?�� ?��직선??? ?���? ?��반�?? 방향?�� �?리키�?�?,
    // A?�� 방향만을 ?��?��?��면된?��. 
    vector2 calipersA(0,1);
    double ret = (p[right]-p[left]).norm();

    // toNext[i] = p[i]?��?�� ?��?�� ?��까�???�� 방향?�� ?��????��?�� ?��?�� 벡터
    vector<vector2> toNext(n);
    for(int i=0;i<n;++i)
        toNext[i] = (p[(i+1)%n] - p[i]).normalize();
    
    int a = left, b = right;

    // �? 바�?? ?��?��?�� ?�� ?��분이 ?���? ?��치�?? 바�?? ?��까�?? 계속?��?��.
    while(a!= right || b != left){
        // a?��?�� ?��?�� ?��까�???�� 각도??? b?��?�� ?��?�� ?��까�???�� 각도 �? ?��?�� 쪽이 ?��???�? ?��?��
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
