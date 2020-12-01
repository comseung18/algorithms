#include <bits/stdc++.h>
using namespace std;

struct RankedDisjointSet{
    vector<int> parent,rank;
    RankedDisjointSet(int n): parent(n), rank(n+1){
        for(int i=0;i<n;++i)
            parent[i] = i;
    }
    // u 가 속한 트리의 루트의 번호를 반환한다.
    int find(int u){
        if(u == parent[u] ) return u;
        return parent[u] = find(parent[u]);
    }
    // u 가 속한 트리와 v가 속한 트리를 합친다.
    void merge(int u, int v){
        u = find(u);
        v = find(v);
        if(u==v) return;
        if(rank[u] > rank[v]) swap(u,v);
        // rank[v] >= rank[u]
        parent[u] = v;
        if(rank[u] == rank[v]) ++rank[v];
    }
};