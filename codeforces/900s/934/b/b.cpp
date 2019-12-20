#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int k; cin >> k;
    if (k > 36) {
        cout << -1 << '\n';
        return 0;
    }
    for (int i = 0; i < 18; i++) {
        if (k >= 2) {
            cout << 8;
            k -= 2;
        }
        else if (k == 1) {
            cout << 4;
            k--;
        }
        else {
            cout << 1;
        }
    }
    cout << '\n';
}

