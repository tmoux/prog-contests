#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ans = 0;
void factor(int x) {
    for (int i = 2; i*i <= x; i++) {
        if (x % i == 0) {
            while (x % i == 0) {
                x /= i;
                ans++;
            }
            factor(x);
            return;
        }
    }
    if (x > 1) ans++;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int x; cin >> x;
    factor(x);
    cout << ans << '\n';
}

