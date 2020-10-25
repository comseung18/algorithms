#include <./vector2.h>

const double EPSILON = 1e-9;
// ?›? ?—?„œ ë²¡í„° bê°? ë²¡í„° a?˜ ë°˜ì‹œê³? ë°©í–¥?´ë©? ?–‘?ˆ˜,
// ?‹œê³„ë°©?–¥?´ë©? ?Œ?ˆ˜, ?‰?–‰?´ë©? 0?„ ë°˜í™˜
double ccw(vector2 a, vector2 b){
    return a.cross(b);
}

// ?  p ë¥? ê¸°ì???œ¼ë¡? ë²¡í„° bê°? ë²¡í„° a?˜ ë°˜ì‹œê³? ë°©í–¥?´ë©? ?Œ?ˆ˜,
// ?‹œê³? ë°©í–¥?´ë©? ?Œ?ˆ˜, ?‰?–‰?´ë©? 0 ?„ ë°˜í™˜

double ccw(vector2 p, vector2 a, vector2 b){
    return ccw(a-p,b-p);
}

// (a,b) ë¥? ?¬?•¨?•˜?Š” ?„ ê³? (c,d) ë¥? ?¬?•¨?•˜?Š” ?„ ?˜ êµì ?„ x ?— ë°˜í™˜?•œ?‹¤.
// ?‘ ?„ ?´ ?‰?–‰?´ë©? (ê³‚ì¹˜?Š” ê²½ìš°ë¥? ?¬?•¨) ê±°ì§“?„, ?•„?‹ˆë©? ì°¸ì„ ë°˜í™˜?•œ?‹¤.
bool lineIntersection(vector2 a, vector2 b,
vector2 c, vector2 d, vector2& x){
    double det = (b-a).cross(d-c);

    // ?‘ ?„ ?´ ?‰?–‰?¸ ê²½ìš°
    if(fabs(det)  < EPSILON) return false;
    x = a + (b-a)*((c-a).cross(d-c)/det);
    return true;
}

// (a,b)??? (c,d)ê°? ?‰?–‰?•œ ?‘ ?„ ë¶„ì¼ ?•Œ 
// ?´?“¤?´ ?•œ ? ?—?„œ ê³‚ì¹˜?Š” ì§? ?™•?¸?•˜?‹¤
bool parallelSegments(vector2 a, vector2 b,
vector2 c, vector2 d, vector2 &p){
    if(b < a) swap(a,b);
    if(d<c) swap(c,d);
    // ?•œ ì§ì„  ?œ„?— ?—†ê±°ë‚˜ ?‘ ?„ ë¶„ì´ ê²¹ì¹˜ì§? ?•Š?Š” ê²½ìš°ë¥? ?š°?„  ê±¸ëŸ¬?‚¸?‹¤.
    if(ccw(a,b,c) != 0 || b <c || d < a) return false;
    
    if(a<c) p =c; else p=a;
    return true;
}

// p ê°? (a,b) ë¥? ê°ì‹¸ë©´ì„œ ê°? ë³??´ x,y ì¶•ì— ?‰?–‰?•œ ìµœì†Œ ?‚¬ê°í˜• ?‚´ë¶??— ?ˆ?Š”ì§? ?™•?¸?•œ?‹¤.
// a,b,p ?Š” ?¼ì§ì„  ?•ˆ?— ?ˆ?‹¤ê³? ê°?? •?•œ?‹¤.
bool inBoundingRectangle(vector2 p, vector2 a, vector2 b){
    if(b<a) swap(a,b);
    return p==a || p==b || (a<p) && (p<b);
}

// (a,b) ?„ ë¶„ê³¼ (c,d) ?„ ë¶„ì˜ êµì ?„ p ?— ë°˜í™˜?•œ?‹¤.
// êµì ?´ ?—¬?Ÿ¬ ê°œì¼ ê²½ìš° ?•„ë¬? ? ?´?‚˜ ë°˜í™˜?•œ?‹¤.
// ?‘ ?„ ë¶„ì´ êµì°¨?•˜ì§? ?•Š?„ ê²½ìš° false ë¥? ë°˜í™˜?•œ?‹¤.
bool segmentIntersection(vector2 a, vector2 b,
vector2 c, vector2 d, vector2&p){

    // ?‘ ì§ì„ ?´ ?‰?–‰?¸ ê²½ìš°ë¥? ?š°?„  ?˜ˆ?™¸ë¡? ì²˜ë¦¬?•œ?‹¤.
    if(!lineIntersection(a,b,c,d,p))
        return parallelSegments(a,b,c,d,p);
    
    // p ê°? ?‘ ?„ ë¶„ì— ?¬?•¨?˜?–´ ?ˆ?Š” ê²½ìš°?—ë§? ì°¸ì„ ë°˜í™˜?•œ?‹¤.
    return inBoundingRectangle(p,a,b) &&
    inBoundingRectangle(p,c,d);
}

// ?‘ ?„ ë¶„ì´ ?„œë¡? ? ‘ì´‰í•˜?Š”ì§? ?—¬ë¶?ë¥? ë°˜í™˜?•œ?‹¤.
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d){
    double ab = ccw(a,b,c)*ccw(a,b,d);
    double cd = ccw(c,d,a)*ccw(c,d,b);

    // ?‘ ?„ ë¶„ì´ ?•œ ì§ì„  ?œ„?— ?ˆê±°ë‚˜ ?? ?´ ê³‚ì¹˜?Š” ê²½ìš°
    if(ab== 0 && cd == 0){
        if(b<a) swap(a,b);
        if(d<c) swap(c,d);
        return !(b<c || d<a);
    }
    return ab <= 0 && cd <= 0;
}

// ?  qê°? ?‹¤ê°í˜• p ?•ˆ?— ?¬?•¨?˜?–´ ?ˆ?„ ê²½ìš° ì°?, ?•„?‹Œ ê²½ìš°
// ê±°ì§“?„ ë°˜í™˜?•œ?‹¤. qê°? ?‹¤ê°í˜•?˜ ê²½ê³„ ?œ„?— ?ˆ?Š” ê²½ìš°?˜
// ë°˜í™˜ ê°’ì?? ? •?˜?˜?–´ ?ˆì§? ?•Š?‹¤.
bool isInside(vector2 q, const vector<vector2>&p){
    int crosses = 0;
    for(int i=0;i<p.size();++i){
        int j =(i+1)%p.size();
        // (p[i],p[j])ê°? ë°˜ì§?„ ?„ ?„¸ë¡œë¡œ ê°?ë¡œì??ë¥´ëŠ”ê°??
        if((p[i].y > q.y) != (p[j].y > q.y)){
            double atX = (p[j].x - p[i].x)*(q.y - p[i].y)/
            (p[j].y - p[i].y) + p[i].x;
            if(q.x < atX) ++crosses;
        }
    }
    return crosses%2 > 0;
}

typedef vector<vector2> polygon;

// ì£¼ì–´ì§? ?‹¨?ˆœ ?‹¤ê°í˜• p?˜ ?„“?´ë¥? êµ¬í•œ?‹¤.
// p?Š” ê°? ê¼?ì§?? ?˜ ?œ„ì¹? ë²¡í„°?˜ ì§‘í•©?œ¼ë¡? ì£¼ì–´ì§„ë‹¤.
double area(const polygon& p){
    double ret = 0;
    for(int i=0;i<p.size();++i){
        int j = (i+1)%p.size();
        ret += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return fabs(ret)/2.0;
}
// points ?— ?ˆ?Š” ? ?“¤?„ ëª¨ë‘ ?¬?•¨?•˜?Š” ìµœì†Œ?˜ ë³¼ë¡ ?‹¤ê°í˜•?„ ì°¾ëŠ”?‹¤.
polygon giftWrap(const vector<vector2> & points){
    int n = points.size();
    polygon hull;

    vector2 pivot = *min_element(points.begin(),points.end());
    hull.push_back(pivot);
    while(1){
        //ph ?—?„œ ?‹œ?‘?•˜?Š” ë²¡í„°ê°? ê°??¥ ?™¼ìª½ì¸ ?  next ë¥? ì°¾ëŠ”?‹¤.
        //?‰?–‰?¸ ? ?´ ?—¬?Ÿ¬ ê°? ?ˆ?œ¼ë©? ê°??¥ ë¨? ê²ƒì„ ?„ ?ƒ?•œ?‹¤.
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

// ?‘ ?‹¤ê°í˜•?´ ?„œë¡? ?‹¿ê±°ë‚˜ ê³‚ì¹˜?Š”ì§? ?—¬ë¶?ë¥? ë°˜í™˜?•œ?‹¤.
// ?•œ ? ?´?¼?„ ê³‚ì¹œ?‹¤ë©? trueë¥? ë°˜í™˜?•œ?‹¤.
bool polygonIntersects(const polygon& p, const polygon& q){
    int n = p.size(), m= q.size();
    // ?š°?„  ?•œ ?‹¤ê°í˜•?´ ?‹¤ë¥? ?‹¤ê°í˜•?— ?¬?•¨?˜?–´ ?ˆ?Š” ê²½ìš°ë¥?
    // ?™•?¸?•˜?.
    if(isInside(p[0],q) || isInside(q[0],p)) return true;

    // ?´ ?™¸?˜ ê²½ìš°, ?‘ ?‹¤ê°í˜•?´ ?„œë¡? ê³‚ì¹œ?‹¤ë©? ?„œë¡? ?‹¿?Š” ?‘ë³??´
    // ë°˜ë“œ?‹œ ì¡´ì¬?•œ?‹¤.
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            if(segmentIntersects(p[i],p[(i+1)%n],
            q[j],q[(j+1)%m])) return true;
    return false;
}

// ë°˜ì‹œê³? ë°©í–¥?œ¼ë¡? ì£¼ì–´ì§?
// ?‘ "ë³¼ë¡" ?‹¤ê°í˜•?˜ ê²¹ì³ì§? ë¶?ë¶„ì˜ ?„“?´ë¥? êµ¬í•œ?‹¤.
// ?´ ?•Œ ê°? ë³¼ë¡ ?‹¤ê°í˜•?˜ ê¼?ì§“ì ??? ?‹¤ë¥? ë³¼ë¡ ?‹¤ê°í˜•?˜
// ë³? ?œ„?— ?—†?‹¤ê³? ê°?? •?•œ?‹¤.
double polygonIntersection(const polygon& p, const polygon& q){
    // ?„œë¡? ?‹¿ì§? ?•Š?Š” ê²½ìš°ë¥? ?˜ˆ?™¸ì²˜ë¦¬
    if(!polygonIntersects(p,q)) return 0;

    // ê²¹ì³ì§? ë³¼ë¡ ?‹¤ê°í˜•??? 
    // p ?•ˆ?— ?ˆ?Š” q ?˜ ê¼?ì§“ì 
    // q ?•ˆ?— ?ˆ?Š” p ?˜ ê¼?ì§“ì 
    // p??? q ?˜ ?„ ë¶„ì˜ êµì ?“¤
    // ?„ ?´?š©?•˜?—¬ ë§Œë“¤?–´ì§„ë‹¤.
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

    // v?˜ ? ?“¤?„ ?´?š©?•´ ì»¨ë°±?Š¤????„ êµ¬ì„±?•œ?‹¤.
    polygon c = giftWrap(v);
    // c ?˜ ?„“?´ë¥? êµ¬í•œ?‹¤.
    return area(c);
            
}

// ê·¸ë¼?•¨?Š¤ìº”ì„ ?´?š©?•´ convexHull ?„ ì°¾ìŒ
// points ?˜ vector ê°? sorting ?˜ë¯?ë¡? ë³?ê²½ë¨?„ ì£¼ì˜!
polygon grahamScan(vector<vector2>& points){
    // y ì¢Œí‘œê°? ê°??¥ ?‚®??? ? ?„ ?„ ?ƒ
    // ê·¸ëŸ¬?•œ ? ?´ ?—¬?Ÿ¬ê°? ?¼ë©? x ê°? ê°??¥ ?‚®??? ?  ?„ ?ƒ
    sort(points.begin(),points.end(),
    [](const vector2& v1, const vector2& v2){
        return v1.y != v2.y ? v1.y < v2.y : v1.x < v2.x;
    });

    vector2 pivot = points[0];
    // x ì¶? pivot ê³? ?´ë£¨ëŠ” ê°ì´ ?‘??? ?ˆœ?„œë¡? ? •? ¬
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

// ?‹œê³? ë°˜ë?? ë°©í–¥?œ¼ë¡? ì£¼ì–´ì§? ë¸”ë¡ ?‹¤ê°í˜•?—?„œ ê°??¥ ë¨? ê¼?ì§“ì  ?Œ ?‚¬?´?˜ ê±°ë¦¬ë¥? ë°˜í™˜?•œ?‹¤.
double diameter(const polygon& p){
    int n = p.size();
    // ?š°?„  ê°??¥ ?™¼ìª½ì— ?ˆ?Š” ? ê³? ?˜¤ë¥¸ìª½?— ?ˆ?Š” ? ?„ ì°¾ëŠ”?‹¤.
    int left = min_element(p.begin(),p.end()) - p.begin();
    int right = max_element(p.begin(), p.end()) - p.begin();

    //p[left] ??? p[right] ?— ê°ê° ?ˆ˜ì§ì„ ?„ ë¶™ì¸?‹¤. ?‘ ?ˆ˜ì§ì„ ??? ?„œë¡? ? •ë°˜ë?? ë°©í–¥?„ ê°?ë¦¬í‚¤ë¯?ë¡?,
    // A?˜ ë°©í–¥ë§Œì„ ?‘œ?˜„?•˜ë©´ëœ?‹¤. 
    vector2 calipersA(0,1);
    double ret = (p[right]-p[left]).norm();

    // toNext[i] = p[i]?—?„œ ?‹¤?Œ ? ê¹Œì???˜ ë°©í–¥?„ ?‚˜????‚´?Š” ?‹¨?œ„ ë²¡í„°
    vector<vector2> toNext(n);
    for(int i=0;i<n;++i)
        toNext[i] = (p[(i+1)%n] - p[i]).normalize();
    
    int a = left, b = right;

    // ë°? ë°”í?? ?Œ?•„?„œ ?‘ ?„ ë¶„ì´ ?„œë¡? ?œ„ì¹˜ë?? ë°”ê?? ?•Œê¹Œì?? ê³„ì†?•œ?‹¤.
    while(a!= right || b != left){
        // a?—?„œ ?‹¤?Œ ? ê¹Œì???˜ ê°ë„??? b?—?„œ ?‹¤?Œ ? ê¹Œì???˜ ê°ë„ ì¤? ?–´?Š ìª½ì´ ?‘???ì§? ?™•?¸
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
