#include <bits/stdc++.h>

using namespace std;

class UnionFind
{
private:
    vector<int> p, type, rnk, sz;

public:
    UnionFind(int n){
        rnk.assign(n, 0);
         sz.assign(n, 1);

        p.resize(n);
        for (int i = 0; i < n; i++) p[i] = i;
    }

    int findSet(int i){return (p[i] == i) ? i : (p[i] = findSet(p[i]));}

    bool isSameSet(int i, int j){return findSet(i) == findSet(j);}

    void Union(int i, int j){
        int x = findSet(i), y = findSet(j);
        if (x != y){
            if (rnk[x] >= rnk[y]){
                p[y] = x, sz[x] += sz[y];
                if (rnk[x] == rnk[y]) rnk[x]++;
            }
            else{
                p[x] = y, sz[y] += sz[x];
            }
        }
    }

    int sizeOfSet(int i){return sz[findSet(i)];}
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}
