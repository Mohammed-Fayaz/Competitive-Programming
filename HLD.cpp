#include <bits/stdc++.h>

using namespace std;

const int LG_N = 20, INF = (int)1e9;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

struct node{
    int v;
    int w;
    int id;
    node(){v = 0, w = 0, id = 0;}
    node(int _v, int _w, int _id) : v(_v), w(_w), id(_id){};
};

vector< vector<node> > graph;

class SegmentTree
{
private:
    vi st, A;
    int n;
    int left (int p){return (p << 1);}
    int right(int p){return (p << 1) + 1;}

    void build(int p, int L, int R){
        if (L == R) st[p] = A[L];
        else{
            build( left(p), L, (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R);
            st[p] = st[left(p)] + st[right(p)];
        }
    }

    int rq(int p, int L, int R, int i, int j){
        if (L >  j || R <  i) return 0;
        if (L >= i && R <= j) return st[p];

        return rq(left(p), L, (L + R) / 2, i, j) + rq(right(p), (L + R) / 2 + 1, R, i, j);
    }

    void update(int p, int L, int R, int k, int v){
        if (L == R) st[p] = v;
        else{
            if (k <= (L + R) / 2) update( left(p), L, (L + R) / 2, k, v);
            else                  update(right(p), (L + R) / 2 + 1, R, k, v);

            st[p] = st[left(p)] + st[right(p)];
        }
    }

public:
    SegmentTree(const vi &_A){
        A = _A; n = (int)A.size();
        st.assign(4 * n, 0);
        build();
    }

    void build(){
        build(1, 0, n - 1);
    }

    int rq(int i, int j){
        return rq(1, 0, n - 1, i, j);
    }

    void update(int k, int v){
        update(1, 0, n - 1, k, v);
    }
};

vi lvl;
vector<vi> p;
void dfsLvl(int u, int par){
    for (auto node : graph[u]){
        int v = node.v, w = node.w;
        if (v == par) continue;
        lvl[v] = 1 + lvl[u]; p[v][0] = u;
        dfsLvl(v, u);
    }
}

int LCA(int u, int v){
    int i, lg;
    if (lvl[u] < lvl[v]) swap(u, v);

    for (lg = 0; (1 << lg) <= lvl[u]; lg++); lg--;

    for (i = lg; i >= 0; i--){
        if (lvl[u] - (1 << i) >= lvl[v]) u = p[u][i];
    }

    if (u == v) return u;

    for (i = lg; i >= 0; i--){
        if (p[u][i] != 0 && p[u][i] != p[v][i]) u = p[u][i], v = p[v][i];
    }

    return p[u][0];
}

vi sz;
void dfsSz(int u, int par){
    sz[u] = 1;
    for (auto &node : graph[u]){
        int v = node.v, w = node.w;
        if (v == par) continue;
        dfsSz(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[graph[u][0].v]) swap(node, graph[u][0]);
    }
}

int dfsNum;
vi in, rin, out, head, base, rid;
void dfsHLD(int u, int par){
    in[u] = dfsNum++;
    rin[in[u]] = u;
    for (auto node : graph[u]){
        int v = node.v, w = node.w, id = node.id;
        if (v == par) continue;
        head[v] = (v == graph[u][0].v ? head[u] : v);
        base.push_back(w);
        rid[id] = dfsNum;
        dfsHLD(v, u);
    }
    out[u] = dfsNum;
}

int main()
{
    int n; scanf("%d", &n);

    graph.assign(n, vector<node>());

    for (int i = 0; i < n - 1; i++){
        int u, v, w; scanf("%d %d %d", &u, &v, &w); u--, v--;
        graph[u].emplace_back(v, w, i);
        graph[v].emplace_back(u, w, i);
    }

    lvl.assign(n, 0);
    p.assign(n, vector<int>(LG_N, -1));
    dfsLvl(0, -1);

    for (int j = 1; j < LG_N; j++){
        for (int i = 0; i < n; i++) if (p[i][j - 1] != -1) p[i][j] = p[p[i][j - 1]][j - 1];
    }

    sz.assign(n, 0);
    dfsSz(0, -1);

    dfsNum = 0;
    in.assign(n, 0), out.assign(n, 0), rin.assign(n, 0), head.assign(n, 0), rid.assign(n, 0);
    base.push_back(0);
    dfsHLD(0, -1);

    SegmentTree st(base);

    auto queryUp = [&](int u, int v){
        if (lvl[u] < lvl[v]) return 0;

        int res = 0;
        while(head[u] != head[v]){
            res += st.rq(in[head[u]], in[u]);
            u = p[head[u]][0];
        }

        res += st.rq(in[v] + 1, in[u]);
        return res;
    };

    auto query = [&](int u, int v){
        return queryUp(u, LCA(u, v)) +  queryUp(v, LCA(u, v));
    };

    auto update = [&](int pos, int w){
        st.update(pos, w);
    };

    int Q; scanf("%d", &Q);
    while(Q--){
        int Qtype; scanf("%d", &Qtype);
        if (Qtype == 1){
            int id, w; scanf("%d %d", &id, &w); id--;
            update(rid[id], w);
        }
        else{
            int u, v; scanf("%d %d", &u, &v); u--, v--;
            printf("%d\n", query(u, v));
        }
    }
    return 0;
}
