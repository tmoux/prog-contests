#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    while (n--) {
        int c, sum; cin >> c >> sum;
        int target = sum/c;
        int extra = sum % c;
        ll ans = 0;
        for (int i = 0; i < extra; i++) {
            ans += (target+1)*(target+1);
        }
        for (int i = 0; i < c-extra; i++) {
            ans += (target)*(target);
        }
        cout << ans << '\n';
    }
}

