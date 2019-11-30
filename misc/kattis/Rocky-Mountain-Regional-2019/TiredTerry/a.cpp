#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, pre[2*maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int p, d; cin >> p >> d;
    string s; cin >> s;
    for (int i = 1; i <= n; i++) {
        pre[i] = s[i-1] == 'Z';
        pre[i+n] = pre[i];
    }
    for (int i = 1; i <= 2*n; i++) {
        pre[i] += pre[i-1];
    }
    int ans = 0;
    for (int i = n+1; i <= 2*n; i++) {
        int cnt = pre[i] - pre[i-p];
        cout << i << ": " << cnt << '\n';
        if (cnt < d) ans++;
    }
    cout << ans << '\n';
}

