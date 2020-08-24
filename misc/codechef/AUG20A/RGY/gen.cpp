#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    random_device device;
    mt19937 gen(device());
    int t, n, m; cin >> t >> n >> m;
    cout << t << '\n';
    while (t--) {
        cout << n << ' ' << m << '\n';
        /*
        for (int i = 1; i <= n; i++) {
            for (int j = i+1; j <= n; j++) {
                cout << i << ' ' << j << '\n';
            }
        }
        */
        set<pair<int,int>> s;
        for (int i = 0; i < m; i++) {
            int u, v;
            do {
                u = gen() % n + 1;
                v = gen() % n + 1;
            } while (u == v || s.count({u,v}) || s.count({v,u}));
            s.insert({u,v});
            cout << u << ' ' << v << '\n';
        }
    }
}
