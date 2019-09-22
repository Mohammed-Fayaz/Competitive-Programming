#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

class UnionFind
{
private:
    vi p, Rank;
public:
    UnionFind(int n){ Rank.assign(n, 0);
    p.assign(n, 0); for (int i = 0; i < n; i++) p[i] = i;}
    int findSet(int i){return (p[i] == i) ? i : (p[i] = findSet(p[i]));}
    bool isSameSet(int i, int j) {return findSet(i) == findSet(j);}
    void unionSet(int i, int j)
    {
        if (!isSameSet(i, j)){
            int x = findSet(i); int y = findSet(j);
            if (Rank[x] > Rank[y]) p[y] = x;
            else {
                p[x] = y;
                if (Rank[x] == Rank[y]) Rank[y]++;
            }
        }
    }
};

int main()
{
    int e, n, u, v, w;
    scanf("%d %d", &n, &e);
    vector<pair<int, ii> > edgeList;
    for (int i = 0; i < e; i++){
        scanf("%d %d %d", &u, &v, &w);
        edgeList.push_back(make_pair(w, make_pair(u, v)));
    }
    sort(edgeList.begin(), edgeList.end());

    int mstCost = 0;
    UnionFind UF(n);
    for (int i = 0; i < e; i++){
        pair<int, ii> Front = edgeList[i];
        if (!UF.isSameSet(Front.second.first, Front.second.second)){
            mstCost += Front.first;
            UF.unionSet(Front.second.first, Front.second.second);
        }
    }

    printf("The Minimum Cost is %d\n", mstCost);
    return 0;
}
