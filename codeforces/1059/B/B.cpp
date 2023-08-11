#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int n, m;
bool grid[maxn][maxn];
bool mark[maxn][maxn];

void f(int i, int j) {
    bool can = true;
    for (int a = 0; a < 3; a++) {
        for (int b = 0; b < 3; b++) {
            if (a == 1 && b == 1) continue;
            if (!grid[i+a][j+b]) can = false;
        }
    }
    if (can) {
        for (int a = 0; a < 3; a++) {
            for (int b = 0; b < 3; b++) {
                if (a == 1 && b == 1) continue;
                mark[i+a][j+b] = true;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            grid[i][j] = s[j] == '#';
        }
    }
    for (int i = 0; i < n - 2; i++) {
        for (int j = 0; j < m - 2; j++) {
            if (grid[i][j]) f(i,j);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] && !mark[i][j]) {
                cout << "NO" << '\n';
                return 0;
            }
        }
    }
    cout << "YES" << '\n';

    return 0;
}

