#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
bool has[maxn][3];
int n, mn[3], cost[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < 3; i++) mn[i] = 987654321;
    for (int i = 0; i < n; i++) {
        cin >> cost[i];
        string s; cin >> s;
        for (char c: s) {
            has[i][c-'A'] = true;
        }
        for (int j = 0; j < 3; j++) {
            if (has[i][j]) mn[j] = min(mn[j],cost[i]);
        }
    }
    int ans = 987654321;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            bool h[3];
            for (int k = 0; k < 3; k++) {
                h[k] = has[i][k] | has[j][k];
            }
            int c = i == j ? cost[i] : cost[i]+cost[j];
            for (int k = 0; k < 3; k++) {
                if (!h[k]) c += mn[k];
            }
            ans = min(ans,c);
        }
    }
    if (ans >= 987654321) {
        cout << -1 << '\n';
    }
    else {
        cout << ans << '\n';
    }

    return 0;
}

