#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e4 + 4;

int gcd(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b > 0) {
        int t = a % b;
        a = b;
        b = t;
    }

    return a;
}

int ans[MAXN];
int m, k;

void dfs(int idx, int g) {
    if (idx == m) {
        ++ans[g];
        return;
    }

    for (int v = -k; v <= k; ++v) {
        dfs(idx + 1, gcd(v, g));
    }
}

int main() {
    cin >> m >> k;

    dfs(0, 0);
    cout << ans[0] + ans[1] << '\n';
    return 0;
}
