#include <bits/stdc++.h>

using namespace std;

template<typename T>
class SegmentTree
{
public:
    int n;
    vector<T> st, A;
    int  left(int p){return (p << 1);}
    int right(int p){return (p << 1) + 1;}

    void build(int p, int L, int R){
        if (L == R) st[p] = A[L];
        else{
            build(left(p), L, (L + R) / 2);
            build(right(p), (L + R) / 2 + 1, R);
            st[p] = st[left(p)] + st[right(p)];
        }
    }

    T rq(int p, int L, int R, int i, int j){
        if (i > R || j < L) return 0;
        if (L >= i && R <= j) return st[p];

        return rq(left(p), L, (L + R) / 2, i, j) + rq(right(p), (L + R) / 2 + 1, R, i, j);
    }

    void update(int p, int L, int R, int k, T v){
        if (L == R){
            st[p] = v;
            return;
        }
        if (L <= k && k <= (L + R) / 2) update(left(p), L, (L + R) / 2, k, v);
        else update(right(p), (L + R) / 2 + 1, R, k, v);
        st[p] = st[left(p)] + st[right(p)];
    }

public:
    SegmentTree(const vector<T> &_A){
        A = _A, n = (int)A.size();
        st.assign(4 * n, 0);
        build();
    }

    void build(){
        build(1, 0, n - 1);
    }

    T rq(int i, int j){
        return rq(1, 0, n - 1, i, j);
    }

    void update(int k, T v){
        update(1, 0, n - 1, k, v);
    }
};

int main()
{
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);

    int n; cin >> n;

    vector<int> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    SegmentTree<int> st(A);

    int Q; cin >> Q;

    while(Q--){
        int taskID; cin >> taskID;
        if (taskID == 1){
            //query
            int i, j; cin >> i >> j;
            cout << st.rq(i - 1, j - 1) << endl;
        }
        else{
            //update
            int k, v; cin >> k >> v;
            st.update(k - 1, v);
        }
    }
    return 0;
}
