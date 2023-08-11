#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int pre[800];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> pre[i];
        pre[i+n] = pre[i];
    }
    for (int i = 1; i <= 2*n; i++) {
        pre[i] += pre[i-1];
    }
    int ans = 360;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j < i+n; j++) {
            int sum = pre[j] - pre[i];
            ans = min(ans,abs(sum-(360-sum)));
        }
    }
    cout << ans << '\n';
}

