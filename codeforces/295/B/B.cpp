#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 505;
int n, d[maxn][maxn], arr[maxn];
ll ans[maxn];
bool vis[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> d[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (int i = n - 1; i >= 0; i--) {
        int w = arr[i];
        vis[w] = true;
        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                d[u][v] = min(d[u][v],d[u][w] + d[w][v]);
                if (vis[u] && vis[v]) {
                    ans[i] += d[u][v];
                }
            }
        }
    }

    //output
    for (int i = 0; i < n; i++) {
        cout << ans[i] << (i == n - 1 ? '\n' : ' ');
    }

    return 0;
}
	

