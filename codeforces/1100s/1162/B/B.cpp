#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 55;
int a[maxn][maxn], b[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
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
        for (int j = 0; j < m; j++) {
            if (a[i][j] > b[i][j]) {
                swap(a[i][j],b[i][j]);
            }
        }
    }
    bool poss = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i > 0 && a[i][j] <= a[i-1][j]) poss = false;
            if (i > 0 && b[i][j] <= b[i-1][j]) poss = false;
            if (j > 0 && a[i][j] <= a[i][j-1]) poss = false;
            if (j > 0 && b[i][j] <= b[i][j-1]) poss = false;
        }
    }
    cout << (poss ? "Possible" : "Impossible") << '\n';
}

