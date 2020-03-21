#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n, m, p;
ll a[maxn], b[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> p;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    int pa = 0, pb = 0;
    for (int t = 0; ; t++) {
        if (pa+pb > t) continue;
        ll tr = (a[pa]*b[pb]) % p;
        if (tr != 0) {
            cout << t << '\n';
            return 0;
        }
        if (a[pa] % p == 0) pa++;
        if (b[pb] % p == 0) pb++;
    }
}

