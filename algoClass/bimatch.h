#include <bits/stdc++.h>
using namespace std;

namespace bimat{
  const int MAX_N = 1;
  const int MAX_M = 1;
  // A와 B의 정점의 개수
  int n,m;
  // adj[i][j]= Ai 와 Bj 가 연결되어 있는가?
  bool adj[MAX_N][MAX_M];
  // 각 정점에 매칭된 상대 정점의 번호를 저장한다.
  vector<int> aMatch, bMatch;
  // dfs() 의 방문여부
  vector<bool> visited;
  // A의 정점인 a 에서 B의 매칭되지 않은 정점으로 가는 경로를 찾는다.
  bool dfs(int a){
    if(visited[a]) return false;
    visited[a] = true;
    for(int b=0;b<m;++b)
      if(adj[a][b])
        // b 가 이미 배정되어 있다면 bMatch[b]에서 부터 시작해 증가경로를 찾는다.
        if(bMatch[b] == -1 || dfs(bMatch[b])){
          // 증가 경로 발견! a와 b를 매치시킨다.
          aMatch[a] = b;
          bMatch[b] = a;
          return true;
        }
    return false;
  }
  // aMatch, bMatch 배열을 계산하고 최대 매칭의 크기를 반환한다.
  int bipartiteMatch(){
    // 처음에는 어떤 정점도 연결되어 있지 않다.
    aMatch = vector<int>(n,-1);
    bMatch = vector<int>(m,-1);
    int size = 0;
    for(int start = 0; start<n;++start){
      visited = vector<bool>(n,false);
      if(dfs(start)) ++size;
    }
    return size;
  }
}
