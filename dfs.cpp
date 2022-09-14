#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;

    vector<vector<int>> graph(n, vector<int>());

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
    }

    function<void(int)> dfs = [&](int u) {
        cout << u << " ";
        for (auto v: graph[u]) {
            dfs(v);
        }
    };

    dfs(0);
    return 0;
}