#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505;
int n, m, a[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = n-1; i >= 0; i--) {
        for (int j = m-1; j >= 0; j--) {
            if (a[i][j] == 0) {
                a[i][j] = min(a[i+1][j],a[i][j+1])-1;
            }
        }
    }
    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
    */
    bool good = true;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (a[i][j] <= a[i][j-1]) {
                good = false;
                break;
            }
        }
    }
    for (int j = 0; j < m; j++) {
        for (int i = 1; i < n; i++) {
            if (a[i][j] <= a[i-1][j]) {
                good = false;
                break;
            }
        }
    }
    if (good) {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans += a[i][j];
            }
        }
        cout << ans << '\n';
    }
    else {
        cout << -1 << '\n';
    }
}

