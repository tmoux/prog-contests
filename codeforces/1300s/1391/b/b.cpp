#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
char a[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
            }
        }
        int ans = 0;
        for (int i = 0; i < n-1; i++) {
            if (a[i][m-1] == 'R') ans++;
        }
        for (int j = 0; j < m-1; j++) {
            if (a[n-1][j] == 'D') ans++;
        }
        cout << ans << '\n';
    }
}

