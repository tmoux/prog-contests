#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005;
int n, a[maxn][maxn];

int u[maxn], v[maxn];
vector<int> adj[maxn], rev[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int x = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            if (i == j && a[i][j] > 0) {
                x = i;
            }
            if (a[i][j] > 0) {
                adj[i].push_back(j);
                rev[j].push_back(i);
            }
        }
    }
    queue<int> q;
    q.push(x);
    while (!q.empty()) {
        int i = q.front(); q.pop();
        if (u[i]) continue;
        u[i] = 1;
        for (int j: adj[i]) {
            if (!u[j]) q.push(j);
        }
    }

    q.push(x);
    while (!q.empty()) {
        int i = q.front(); q.pop();
        if (v[i]) continue;
        v[i] = 1;
        for (int j: rev[i]) {
            if (!v[j]) q.push(j);
        }
    }

    int c1 = 0, c2 = 0;
    for (int i = 1; i <= n; i++) {
        if (u[i]) c1++;
        if (v[i]) c2++;
    }
    /*
    cout << c1 << ' ' << c2 << '\n';
    cout << "x = " << x << '\n';
    */
    if (c1 == n && c2 == n) {
        cout << "YES\n";
    }
    else {
        cout << "NO\n";
    }
}

