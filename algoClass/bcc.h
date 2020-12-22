#include <bits/stdc++.h>
using namespace std;

// 간선으로 분리하여 bcc 컴포넌트를 전부 구함
namespace bccAllComponentGet{
    vector<vector<int> > adj;
    typedef pair<int,int> P;
    int vertexCnt;
    vector<int> discovered;
    vector<vector<P> > bcc;
    stack<P> st;

    int dfs(int here, int parent = -1){
        int ret = discovered[here] = vertexCnt++;

        for(int there : adj[here]){
            if(there == parent) continue;

            // 방문하지 않은 간선이면,
            // ex) 트리간선, 역방향간선
            // 순방향간선은 해당 목적지 간선에서
            // 역방향간선으로 st 에 푸시 됨.
            if(discovered[here] > discovered[there])
                st.push({here, there});
            // 역방향 간선
            if(discovered[there] > 0) ret = min(ret, discovered[there]);

            // 트리 간선이면
            else{
                int tmp = dfs(there, here);
                ret = min(ret, tmp);
                // there 에서 here 의 조상 노드로 갈 수 없다면,
                if(tmp >= discovered[here]){
                    // 스택에 있는
                    // 방문하지 않았던 간선을 모아서
                    // bcc 를 구성함.
                    vector<P> tmpBCC;
                    while(!st.empty() && st.top() != P(here, there)){
                        tmpBCC.push_back(st.top());
                        st.pop();
                    }
                    tmpBCC.push_back(st.top());
                    st.pop();
                    bcc.push_back(tmpBCC);
                }
            }
        }
        return ret;
    }
}

// 단순히 단절점 만을 구함
namespace bccCutVertex{
    vector<vector<int> > adj;
    vector<int> discovered;
    // 각 정점이 단절점인지 여부
    vector<bool> isCutVertex;
    int vertexCnt;

    int dfs(int here, bool isRoot){
        int ret = discovered[here] = vertexCnt++;
        // 루트인 경우 절단점 판정을 위해 자손 서브트리의 개수를 센다.
        int children = 0;
        for(int there : adj[here]){
            if(discovered[there] == -1){
                ++children;
                int subtree = dfs(there, false);
                if(!isRoot && subtree >= discovered[here])
                    isCutVertex[here] = true;
                ret = min(ret, subtree);
            }
            else
                ret = min(ret, discovered[there]);
        }
        if(isRoot) isCutVertex[here] = (children >= 2);
        return ret;
    }
}

