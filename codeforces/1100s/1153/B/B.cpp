#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int front[maxn], Left[maxn], top[maxn][maxn];
int ans[maxn][maxn];
int n, m, h;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> h;
    for (int i = 1; i <= m; i++) cin >> front[i];
    for (int i = 1; i <= n; i++) cin >> Left[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> top[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (top[i][j] == 0) continue;
            ans[i][j] = min(front[j],Left[i]);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }
}

