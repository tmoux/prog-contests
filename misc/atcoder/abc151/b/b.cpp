#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k, m; cin >> n >> k >> m;
    int target = m*n;
    for (int i = 0; i < n-1; i++) {
        int ai; cin >> ai;
        target -= ai;
    }
    target = max(0,target);
    if (target > k) {
        cout << -1 << '\n';
    }
    else {
        cout << target << '\n';
    }
}

