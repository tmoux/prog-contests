#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5+5;
int n, m;
vector<int> adj[N];

bool a[N], b[N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        if (y == n) b[x] = true;
        if (x == 1) a[y] = true;
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] && b[i]) {
            cout << "POSSIBLE\n";
            return 0;
        }
    }
    cout << "IMPOSSIBLE\n";
}

