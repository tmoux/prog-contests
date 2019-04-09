#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505;
int n, m;
int a[maxn][maxn], b[maxn][maxn], c[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> b[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        int p = 0;
        for (int j = 0; j < m; j++) {
            if (a[i][j] ^ b[i][j]) p++;
        }
        if (p&1) {
            cout << "No\n";
            return 0;
        }
    }
    for (int j = 0; j < m; j++) {
        int p = 0;
        for (int i = 0; i < n; i++) {
            if (a[i][j] ^ b[i][j]) p++;
        }
        if (p&1) {
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";
}

