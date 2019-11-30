#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int ans = 0;
    int ai; cin >> ai;
    for (int i = 1; i < n; i++) {
        cin >> ai;
        ans += i*ai*4;
    }
    cout << ans << '\n';
}

