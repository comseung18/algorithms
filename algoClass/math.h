#include <bits/stdc++.h>
using namespace std;

// 최대 공약수
int gcd(int a, int b){
    if(b==0) return a;
    return gcd(b,a%b);
}

// 최소 공배수
int lcm(int a, int b){
    return a/gcd(a,b)*b;
}

// 단변수 다항 방정식의 해를 이분법으로 찾기
namespace equation{
// 단일 변수 다항식 p의 계수가 주어질 때 미분한 결과 p' 의 계수를 반환한다.
vector<double> differentiate(const vector<double>& poly);

// 1차 혹은 2차 방정식을 푼다.
vector<double> solveNaive(const vector<double>& poly);

// 다항식 f(x) 의 계수 poly 가 주어질 때, f(x0) 을 반환한다.
double evaluate(const vector<double>& poly, double x0);

// 방정식의 해의 절대 값은 L 이하여하 한다.
const double L = 25;
vector<double> solve(const vector<double>&poly){
    int n = poly.size()-1;
    // 기저 사례: 2차 이하의 방정식은 풀 수 있다.
    if(n<=2) return solveNaive(poly);
    // 방정식을 미분해서 n-1차 방정식을 푼다.
    vector<double> derivative = differentiate(poly);
    vector<double> sols = solve(derivative);
    // 이 극점들 사이를 하나하나 검사하며 근이 있나 확인한다.
    sols.insert(sols.begin(), -L-1);
    sols.insert(sols.end(), L+1);
    vector<double> ret;
    for(int i=0;i+1<sols.size();++i){
        double x1 = sols[1], x2= sols[i+1];
        double y1 = evaluate(poly,x1), y2 = evaluate(poly,x2);
        // f(x1)과 f(x2)의 부호가 같은 경우 답은 없다.
        if(y1*y2 > 0) continue;
        // 불변조건 : f(x1) <= 0 < f(x2)
        if(y1 > y2) {swap(y1,y2); swap(x1,x2);}
        // 이분법을 사용하자
        for(int iter=0;iter<100;++iter){
            double mx = (x1+x2)/2.0;
            double my = evaluate(poly,mx);
            if(y1*my > 0){
                y1 = my;
                x1 = mx;
            }
            else{
                y2 = my;
                x2 = mx;
            }
        }
        ret.push_back((x1+x2)/2.0);
    }
    sort(ret.begin(),ret.end());
    return ret;
}


}

// 삼분 검색
namespace ternary{
// 우리가 최대치를 찾고 싶어하는 함수
// 극대 점이 하나밖에 없고, 이 점 왼쪽으로 순증가, 오른쪽으로 순감소 해야한다.
double f(double x);
// [lo,hi] 구간에서 f(x)가 최대치를 갖는 x를 반환한다.
double ternary(double lo, double hi){
    for(int iter=0;iter<100;++iter){
        double a = (2*lo + hi)/3.0;
        double b = (lo + 2*hi)/3.0;
        if(f(a) > f(b)) hi = b;
        else lo = a;
    }
    return (lo+hi)/2.0;
}
}

// 에라토스테네스의 체, eratosthenes
namespace eratosthenes{
    int n;
    const int MAX_N = 100;
    bool isPrime[MAX_N+1];
    // 가장 단순한 형태의 에라토스테네스의 체의 구현
    // 종료한 뒤 isPrime[i] = i 가 소수인가?
    void eratosthenes(){
        memset(isPrime,1,sizeof(isPrime));
        // 1 은 항상 예외 처리
        isPrime[0] = isPrime[1] = false;
        int sqrtn = int(sqrt(n));
        for(int i=2;i<=sqrtn;++i){
            if(isPrime[i])
                for(int j=i*i;j<=n;j+=i) isPrime[j] = false;
        }
    }

    // 에라토스테네스의 체를 이용한 빠른 소인수 분해
    // minFactor[i]= i의 가장 작은 소인수(i가 소수인 경우 자기 자신)
    int minFactor[MAX_N+1];
    void eratosthenes2(){
        minFactor[0] = minFactor[1] = -1;
        for(int i=2;i<=n;++i) minFactor[i] = i;

        int sqrtn = int(sqrt(n));
        for(int i=2;i<=sqrtn;++i){
            if(minFactor[i] == i){
                for(int j=i*i;j<=n;j+=i)
                    if(minFactor[j] == j)
                        minFactor[j] = i;
            }
        }
    }
    // 2 이상의 자연수 n을 소인수 분해한 결과를 반환한다.
    vector<int> factor(int n){
        vector<int> ret;
        // n이 1이 될 때까지 가장작은 소인수로 나누기를 반복
        while(n>1){
            ret.push_back(minFactor[n]);
            n /= minFactor[n];
        }
        return ret;
    }
}

