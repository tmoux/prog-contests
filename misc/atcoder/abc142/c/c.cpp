#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, ans[maxn];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        ans[ai] = i;
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

