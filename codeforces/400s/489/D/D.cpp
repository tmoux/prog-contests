#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3005;
int n, m;
vector<int> inn[maxn], out[maxn];
int cnt[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        inn[b].push_back(a);
        out[a].push_back(b);
    }
    for (int i = 1; i <= n; i++) {
        for (int a : inn[i]) {
            for (int b: out[i]) {
                cnt[a][b]++;
            }
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            ll add = cnt[i][j] * (cnt[i][j] - 1) / 2;
            ans += add;
        }
    }
    cout << ans << '\n';


    return 0;
}

