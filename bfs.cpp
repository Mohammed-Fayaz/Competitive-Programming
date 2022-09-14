#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;

    vector<vector<int>> graph(n, vector<int>());

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
    }

    function<void(int)> bfs = [&](int s) {
        queue<int> q; q.push(s);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            cout << u << " ";
            for (auto v : graph[u]) q.push(v);
        }
    };

    bfs(0);
    return 0;
}
