#include <./vector2.h>

const double EPSILON = 1e-9;
// ?? ?? ๋ฒกํฐ b๊ฐ? ๋ฒกํฐ a? ๋ฐ์๊ณ? ๋ฐฉํฅ?ด๋ฉ? ??,
// ?๊ณ๋ฐฉ?ฅ?ด๋ฉ? ??, ???ด๋ฉ? 0? ๋ฐํ
double ccw(vector2 a, vector2 b){
    return a.cross(b);
}

// ?  p ๋ฅ? ๊ธฐ์???ผ๋ก? ๋ฒกํฐ b๊ฐ? ๋ฒกํฐ a? ๋ฐ์๊ณ? ๋ฐฉํฅ?ด๋ฉ? ??,
// ?๊ณ? ๋ฐฉํฅ?ด๋ฉ? ??, ???ด๋ฉ? 0 ? ๋ฐํ

double ccw(vector2 p, vector2 a, vector2 b){
    return ccw(a-p,b-p);
}

// (a,b) ๋ฅ? ?ฌ?จ?? ? ๊ณ? (c,d) ๋ฅ? ?ฌ?จ?? ? ? ๊ต์ ? x ? ๋ฐํ??ค.
// ? ? ?ด ???ด๋ฉ? (๊ณ์น? ๊ฒฝ์ฐ๋ฅ? ?ฌ?จ) ๊ฑฐ์ง?, ??๋ฉ? ์ฐธ์ ๋ฐํ??ค.
bool lineIntersection(vector2 a, vector2 b,
vector2 c, vector2 d, vector2& x){
    double det = (b-a).cross(d-c);

    // ? ? ?ด ???ธ ๊ฒฝ์ฐ
    if(fabs(det)  < EPSILON) return false;
    x = a + (b-a)*((c-a).cross(d-c)/det);
    return true;
}

// (a,b)??? (c,d)๊ฐ? ??? ? ? ๋ถ์ผ ? 
// ?ด?ค?ด ? ? ?? ๊ณ์น? ์ง? ??ธ??ค
bool parallelSegments(vector2 a, vector2 b,
vector2 c, vector2 d, vector2 &p){
    if(b < a) swap(a,b);
    if(d<c) swap(c,d);
    // ? ์ง์  ?? ?๊ฑฐ๋ ? ? ๋ถ์ด ๊ฒน์น์ง? ?? ๊ฒฝ์ฐ๋ฅ? ?ฐ?  ๊ฑธ๋ฌ?ธ?ค.
    if(ccw(a,b,c) != 0 || b <c || d < a) return false;
    
    if(a<c) p =c; else p=a;
    return true;
}

// p ๊ฐ? (a,b) ๋ฅ? ๊ฐ์ธ๋ฉด์ ๊ฐ? ๋ณ??ด x,y ์ถ์ ??? ์ต์ ?ฌ๊ฐํ ?ด๋ถ?? ??์ง? ??ธ??ค.
// a,b,p ? ?ผ์ง์  ?? ??ค๊ณ? ๊ฐ?? ??ค.
bool inBoundingRectangle(vector2 p, vector2 a, vector2 b){
    if(b<a) swap(a,b);
    return p==a || p==b || (a<p) && (p<b);
}

// (a,b) ? ๋ถ๊ณผ (c,d) ? ๋ถ์ ๊ต์ ? p ? ๋ฐํ??ค.
// ๊ต์ ?ด ?ฌ?ฌ ๊ฐ์ผ ๊ฒฝ์ฐ ?๋ฌ? ? ?ด? ๋ฐํ??ค.
// ? ? ๋ถ์ด ๊ต์ฐจ?์ง? ?? ๊ฒฝ์ฐ false ๋ฅ? ๋ฐํ??ค.
bool segmentIntersection(vector2 a, vector2 b,
vector2 c, vector2 d, vector2&p){

    // ? ์ง์ ?ด ???ธ ๊ฒฝ์ฐ๋ฅ? ?ฐ?  ??ธ๋ก? ์ฒ๋ฆฌ??ค.
    if(!lineIntersection(a,b,c,d,p))
        return parallelSegments(a,b,c,d,p);
    
    // p ๊ฐ? ? ? ๋ถ์ ?ฌ?จ??ด ?? ๊ฒฝ์ฐ?๋ง? ์ฐธ์ ๋ฐํ??ค.
    return inBoundingRectangle(p,a,b) &&
    inBoundingRectangle(p,c,d);
}

// ? ? ๋ถ์ด ?๋ก? ? ์ดํ?์ง? ?ฌ๋ถ?๋ฅ? ๋ฐํ??ค.
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d){
    double ab = ccw(a,b,c)*ccw(a,b,d);
    double cd = ccw(c,d,a)*ccw(c,d,b);

    // ? ? ๋ถ์ด ? ์ง์  ?? ?๊ฑฐ๋ ?? ?ด ๊ณ์น? ๊ฒฝ์ฐ
    if(ab== 0 && cd == 0){
        if(b<a) swap(a,b);
        if(d<c) swap(c,d);
        return !(b<c || d<a);
    }
    return ab <= 0 && cd <= 0;
}

// ?  q๊ฐ? ?ค๊ฐํ p ?? ?ฌ?จ??ด ?? ๊ฒฝ์ฐ ์ฐ?, ?? ๊ฒฝ์ฐ
// ๊ฑฐ์ง? ๋ฐํ??ค. q๊ฐ? ?ค๊ฐํ? ๊ฒฝ๊ณ ?? ?? ๊ฒฝ์ฐ?
// ๋ฐํ ๊ฐ์?? ? ???ด ?์ง? ??ค.
bool isInside(vector2 q, const vector<vector2>&p){
    int crosses = 0;
    for(int i=0;i<p.size();++i){
        int j =(i+1)%p.size();
        // (p[i],p[j])๊ฐ? ๋ฐ์ง? ? ?ธ๋ก๋ก ๊ฐ?๋ก์??๋ฅด๋๊ฐ??
        if((p[i].y > q.y) != (p[j].y > q.y)){
            double atX = (p[j].x - p[i].x)*(q.y - p[i].y)/
            (p[j].y - p[i].y) + p[i].x;
            if(q.x < atX) ++crosses;
        }
    }
    return crosses%2 > 0;
}

typedef vector<vector2> polygon;

// ์ฃผ์ด์ง? ?จ? ?ค๊ฐํ p? ??ด๋ฅ? ๊ตฌํ?ค.
// p? ๊ฐ? ๊ผ?์ง?? ? ?์น? ๋ฒกํฐ? ์งํฉ?ผ๋ก? ์ฃผ์ด์ง๋ค.
double area(const polygon& p){
    double ret = 0;
    for(int i=0;i<p.size();++i){
        int j = (i+1)%p.size();
        ret += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return fabs(ret)/2.0;
}
// points ? ?? ? ?ค? ๋ชจ๋ ?ฌ?จ?? ์ต์? ๋ณผ๋ก ?ค๊ฐํ? ์ฐพ๋?ค.
polygon giftWrap(const vector<vector2> & points){
    int n = points.size();
    polygon hull;

    vector2 pivot = *min_element(points.begin(),points.end());
    hull.push_back(pivot);
    while(1){
        //ph ?? ???? ๋ฒกํฐ๊ฐ? ๊ฐ??ฅ ?ผ์ชฝ์ธ ?  next ๋ฅ? ์ฐพ๋?ค.
        //???ธ ? ?ด ?ฌ?ฌ ๊ฐ? ??ผ๋ฉ? ๊ฐ??ฅ ๋จ? ๊ฒ์ ? ???ค.
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

// ? ?ค๊ฐํ?ด ?๋ก? ?ฟ๊ฑฐ๋ ๊ณ์น?์ง? ?ฌ๋ถ?๋ฅ? ๋ฐํ??ค.
// ? ? ?ด?ผ? ๊ณ์น?ค๋ฉ? true๋ฅ? ๋ฐํ??ค.
bool polygonIntersects(const polygon& p, const polygon& q){
    int n = p.size(), m= q.size();
    // ?ฐ?  ? ?ค๊ฐํ?ด ?ค๋ฅ? ?ค๊ฐํ? ?ฌ?จ??ด ?? ๊ฒฝ์ฐ๋ฅ?
    // ??ธ??.
    if(isInside(p[0],q) || isInside(q[0],p)) return true;

    // ?ด ?ธ? ๊ฒฝ์ฐ, ? ?ค๊ฐํ?ด ?๋ก? ๊ณ์น?ค๋ฉ? ?๋ก? ?ฟ? ?๋ณ??ด
    // ๋ฐ๋? ์กด์ฌ??ค.
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            if(segmentIntersects(p[i],p[(i+1)%n],
            q[j],q[(j+1)%m])) return true;
    return false;
}

// ๋ฐ์๊ณ? ๋ฐฉํฅ?ผ๋ก? ์ฃผ์ด์ง?
// ? "๋ณผ๋ก" ?ค๊ฐํ? ๊ฒน์ณ์ง? ๋ถ?๋ถ์ ??ด๋ฅ? ๊ตฌํ?ค.
// ?ด ? ๊ฐ? ๋ณผ๋ก ?ค๊ฐํ? ๊ผ?์ง์ ??? ?ค๋ฅ? ๋ณผ๋ก ?ค๊ฐํ?
// ๋ณ? ?? ??ค๊ณ? ๊ฐ?? ??ค.
double polygonIntersection(const polygon& p, const polygon& q){
    // ?๋ก? ?ฟ์ง? ?? ๊ฒฝ์ฐ๋ฅ? ??ธ์ฒ๋ฆฌ
    if(!polygonIntersects(p,q)) return 0;

    // ๊ฒน์ณ์ง? ๋ณผ๋ก ?ค๊ฐํ??? 
    // p ?? ?? q ? ๊ผ?์ง์ 
    // q ?? ?? p ? ๊ผ?์ง์ 
    // p??? q ? ? ๋ถ์ ๊ต์ ?ค
    // ? ?ด?ฉ??ฌ ๋ง๋ค?ด์ง๋ค.
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

    // v? ? ?ค? ?ด?ฉ?ด ์ปจ๋ฐฑ?ค???? ๊ตฌ์ฑ??ค.
    polygon c = giftWrap(v);
    // c ? ??ด๋ฅ? ๊ตฌํ?ค.
    return area(c);
            
}

// ๊ทธ๋ผ?จ?ค์บ์ ?ด?ฉ?ด convexHull ? ์ฐพ์
// points ? vector ๊ฐ? sorting ?๋ฏ?๋ก? ๋ณ?๊ฒฝ๋จ? ์ฃผ์!
polygon grahamScan(vector<vector2>& points){
    // y ์ขํ๊ฐ? ๊ฐ??ฅ ?ฎ??? ? ? ? ?
    // ๊ทธ๋ฌ? ? ?ด ?ฌ?ฌ๊ฐ? ?ผ๋ฉ? x ๊ฐ? ๊ฐ??ฅ ?ฎ??? ?  ? ?
    sort(points.begin(),points.end(),
    [](const vector2& v1, const vector2& v2){
        return v1.y != v2.y ? v1.y < v2.y : v1.x < v2.x;
    });

    vector2 pivot = points[0];
    // x ์ถ? pivot ๊ณ? ?ด๋ฃจ๋ ๊ฐ์ด ???? ??๋ก? ? ? ฌ
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

// ?๊ณ? ๋ฐ๋?? ๋ฐฉํฅ?ผ๋ก? ์ฃผ์ด์ง? ๋ธ๋ก ?ค๊ฐํ?? ๊ฐ??ฅ ๋จ? ๊ผ?์ง์  ? ?ฌ?ด? ๊ฑฐ๋ฆฌ๋ฅ? ๋ฐํ??ค.
double diameter(const polygon& p){
    int n = p.size();
    // ?ฐ?  ๊ฐ??ฅ ?ผ์ชฝ์ ?? ? ๊ณ? ?ค๋ฅธ์ชฝ? ?? ? ? ์ฐพ๋?ค.
    int left = min_element(p.begin(),p.end()) - p.begin();
    int right = max_element(p.begin(), p.end()) - p.begin();

    //p[left] ??? p[right] ? ๊ฐ๊ฐ ?์ง์ ? ๋ถ์ธ?ค. ? ?์ง์ ??? ?๋ก? ? ๋ฐ๋?? ๋ฐฉํฅ? ๊ฐ?๋ฆฌํค๋ฏ?๋ก?,
    // A? ๋ฐฉํฅ๋ง์ ???๋ฉด๋?ค. 
    vector2 calipersA(0,1);
    double ret = (p[right]-p[left]).norm();

    // toNext[i] = p[i]?? ?ค? ? ๊น์??? ๋ฐฉํฅ? ?????ด? ?จ? ๋ฒกํฐ
    vector<vector2> toNext(n);
    for(int i=0;i<n;++i)
        toNext[i] = (p[(i+1)%n] - p[i]).normalize();
    
    int a = left, b = right;

    // ๋ฐ? ๋ฐํ?? ??? ? ? ๋ถ์ด ?๋ก? ?์น๋?? ๋ฐ๊?? ?๊น์?? ๊ณ์??ค.
    while(a!= right || b != left){
        // a?? ?ค? ? ๊น์??? ๊ฐ๋??? b?? ?ค? ? ๊น์??? ๊ฐ๋ ์ค? ?ด? ์ชฝ์ด ????์ง? ??ธ
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
