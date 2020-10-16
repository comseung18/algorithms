#include <./vector2.h>

const double EPSILON = 1e-7;
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

