#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    int ans = 0;
    bool inBattle = false;
    for (int i = 0; i < n; i++) {
        if (a[i] == b[i]) {
            if (inBattle) continue;
            else {
                inBattle = true;
            }
        }
        else {
            if (!inBattle) continue;
            else {
                inBattle = false;
                ans++;
            }
        }
    }
    if (inBattle) ans++;
    cout << ans << '\n';
}

