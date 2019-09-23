#include <bits/stdc++.h>

using namespace std;

const int   INF = (int)1e9;
const int MAX_V = 400;

struct edge{
    int u, v, cap, flow;
};

int V, s, t, ptr[MAX_V], dist[MAX_V];
vector<edge> e;
vector<int> g[MAX_V];

void addEdge(int u, int v, int cap){
    edge e1 = {u, v, cap, 0};
    edge e2 = {v, u,   0, 0};

    g[u].push_back((int)e.size());
    e.push_back(e1);

    g[v].push_back((int)e.size());
    e.push_back(e2);
}

bool bfs(){
    memset(dist, -1, sizeof(dist));
    queue<int> q;
    q.push(s);
    dist[s] = 0;
    while(!q.empty() && dist[t] == -1){
        int u = q.front(); q.pop();
        for (int id : g[u]){
            int to = e[id].v;
            if (dist[to] == -1 && e[id].flow < e[id].cap){
                q.push(to);
                dist[to] = dist[u] + 1;
            }
        }
    }
    return dist[t] != -1;
}

int dfs(int v, int flow){
    if (!flow) return 0;
    if (v == t) return flow;

    for(; ptr[v] < g[v].size(); ptr[v]++){
        int id = g[v][ptr[v]], to = e[id].v;
        if (dist[to] != dist[v] + 1) continue;
        int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
        if (pushed){
            e[id].flow += pushed;
            e[id ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}

int dinic(){
    int mf = 0;
    while(true){
        if (!bfs()) break;
        memset(ptr, 0, sizeof(ptr));
        while(int pushed = dfs(s, INF)) mf += pushed;
    }
    return mf;
}

int main()
{
    int V, E; scanf("%d %d", &V, &E);
    for (int i = 0; i < E; i++){
        int u, v, w; scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    scanf("%d %d", &s, &t);
    printf("%d\n", dinic());
}
