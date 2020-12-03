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
    int num;
    explicit vector2(double _x=0, double _y=0,int num=0):
    x(_x),y(_y) {
        this->num = num;
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

double ccw(vector2 a, vector2 b){
    return a.cross(b);
}

double ccw(vector2 p, vector2 a, vector2 b){
    return ccw(a-p,b-p);
}

vb used;
typedef vector<vector2> polygon;
polygon giftWrap(const vector<vector2> & points){
    int n = points.size();
    polygon hull;

    vector2 pivot = *min_element(points.begin(),points.end());
    hull.push_back(pivot);
    used[pivot.num] = true;
    while(1){
        vector2 ph = hull.back(), next = points[0];
        for(int i=1;i<n;++i){
            double cross = ccw(ph, next, points[i]);
            double dist = (next - ph).norm()
            - (points[i]-ph).norm();
            if(cross > 0 || (cross==0 && dist < 0)){
                next = points[i];
            }
                
        }
        if(next == pivot) break;
        hull.push_back(next);
        used[next.num] = true;
    }
    return hull;
}
bool isInside(vector2 q, const vector<vector2>&p){
    int crosses = 0;
    for(int i=0;i<p.size();++i){
        int j =(i+1)%p.size();
        if((p[i].y > q.y) != (p[j].y > q.y)){
            double atX = (p[j].x - p[i].x)*(q.y - p[i].y)/
            (p[j].y - p[i].y) + p[i].x;
            if(q.x < atX) ++crosses;
        }
    }
    return crosses%2 > 0;
}


int main(){
    fastio;
    int N, Px, Py;
    cin >> N >> Px >> Py;
    polygon poly;
    rep(i,N){
        int x,y;
        cin >> x >> y;
        poly.push_back(vector2(x,y,i));
    }
    int cnt =0;
    used = vb(N,false);
    while(1){
        bool b = true;
        polygon t;
        rep(i,poly.size()){
            if(!used[poly[i].num]){
                b= false;
                t.push_back(poly[i]);
            } 
        } 
        if(b) break;
        
        polygon p = giftWrap(t);
        // p 안에 감옥이 있는지 확인
        if(isInside(vector2(Px,Py),p)) ++cnt;
        else break;
    }
    cout << cnt;
    return 0;
}