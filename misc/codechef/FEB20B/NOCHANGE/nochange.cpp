#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int n, p, d[maxn];

int ceil(int a, int b) {
    return (a+b-1)/b;
}

void solve() {
    cin >> n >> p;
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    for (int i = 0; i < n; i++) {
        if (p % d[i] != 0) {
            cout << "YES ";
            for (int j = 0; j < n; j++) {
                if (j != i) cout << 0 << ' ';
                else cout << ceil(p,d[i]) << ' ';
            }
            cout << '\n';
            return;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((p-d[j]) % d[i] != 0) {
                int ni = ceil(p-d[j],d[i]);
                cout << "YES ";
                for (int k = 0; k < n; k++) {
                    if (k == i) cout << ni << ' ';
                    else if (k == j) cout << 1 << ' ';
                    else cout << 0 << ' ';
                }
                cout << '\n';
                return;
            }
        }
    }
    cout << "NO\n";
    return;
}

int main()
{
    int tt; cin >> tt;
    while (tt--) {
        solve();
    }
}
