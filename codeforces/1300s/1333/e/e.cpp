#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int g[500][500];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    if (n < 3) {
        cout << -1 << '\n';
        return 0;
    }
    g[0][0] = n*n;
    g[0][1] = n*n-4;
    g[0][2] = n*n-3;
    g[1][0] = n*n-2;
    g[1][1] = n*n-7;
    g[1][2] = n*n-1;
    g[2][0] = n*n-8;
    g[2][1] = n*n-6;
    g[2][2] = n*n-5;
    int x = n*n-9;
    for (int i = 3; i < n; i++) {
        if (i&1) {
            for (int j = 0; j <= i; j++) {
                g[i][j] = x--;
            }
            for (int j = i-1; j >= 0; j--) {
                g[j][i] = x--;
            }
        }
        else {
            for (int j = 0; j < i; j++) {
                g[j][i] = x--;
            }
            for (int j = i; j >= 0; j--) {
                g[i][j] = x--;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << g[i][j] << ' ';
        }
        cout << '\n';
    }
}
