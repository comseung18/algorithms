#include <bits/stdc++.h>
using namespace std;

namespace scc{
    // 그래프의 인접 리스트 표현
    vector<vector<int> > adj;
    // 각 정점의 컴포넌트 번호. 컴포넌트 번호는 0부터 시작하며,
    // 같은 강결합 컴포넌트에 속한 정점들의 컴포넌트 번호가 같다.
    vector<int> sccId;
    // 각 정점의 발견 순서
    vector<int> discovered;
    // 정점의 번호를 담는 스택
    stack<int> st;
    int sccCounter, vertexCounter;
    // here를 루트로 하는 서브트리에서 역방향 간선이나 교차간선을
    // 통해 갈 수 있는 정점 중 최소 발견 순서를 반환한다
    // (이미 scc로 묶인 정점으로 연결된 교차 간서은 무시한다)
    int scc(int here){
        int ret = discovered[here] = vertexCounter++;
        // 스택에 here를 넣는다. here 의 후손들은 모두 스택에서 here 후에 들어간다.
        st.push(here);
        for(int there: adj[here]){
            // (here, there) 가 트리간선
            if(discovered[there] == -1)
                ret = min(ret, scc(there));
            // there가 무시해야 하는 교차간선이 아니라면
            else if(sccId[there] == -1)
                ret = min(ret, discovered[there]);
        }
        // here에서 부모로 올라가는 간선을 끊어야 할지 확인한다.
        if(ret == discovered[here]){
            // here 를 루트로 하는 서브트리에 남아있는 정점들을 전부 하나의 컴포넌트로 묶는다.
            while(1){
                int t = st.top();
                st.pop();
                sccId[t] = sccCounter;
                if(t==here) break;
            }
            ++sccCounter;
        }
        return ret;
    }

    // tarjan의 SCC 알고리즘
    vector<int> tarjanSCC(){
        // init
        sccId = discovered = vector<int>(adj.size(), -1);
        sccCounter = vertexCounter = 0;
        // 모든 정점에 대해서 scc()
        for(int i=0;i<adj.size(); ++i) if(discovered[i] == -1) scc(i);
        return sccId;
    }
}