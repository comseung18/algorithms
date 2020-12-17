#include <bits/stdc++.h>
using namespace std;

// 위상정렬 알고리즘
namespace topologicalSort{
    vector<vector<int> > adj;
    vector<bool> visited;
    // 위상정렬의 결과를 res 에 반환
    void dfs(int here, vector<int>& res){
        visited[here] = true;
        for(int there: adj[here]){
            if(!visited[there]) dfs(there, res);
        }
        res.push_back(here);
    }
    vector<int> topologicalSort(){
        visited = vector<bool>(adj.size(), false);
        vector<int> ret = vector<int>();
        for(int i=0;i<adj.size();++i) if(!visited[i]) dfs(i,ret);
        reverse(ret.begin(),ret.end());
        return ret;
    }
}