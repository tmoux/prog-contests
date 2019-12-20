#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int a[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int pt = 0;
    if (n&1) {
        for (int i = 2; i <= n; i += 2) {
            a[pt++] = i;
        }
        for (int i = n-1; i >= 2; i -= 2) {
            a[pt++] = i;
        }
        for (int i = 1; i <= n; i += 2) {
            a[pt++] = i;
        }
        for (int i = n-2; i >= 1; i -= 2) {
            a[pt++] = i;
        }
        a[pt++] = n;
    }
    else {
        for (int i = 1; i <= n; i += 2) {
            a[pt++] = i;
        }
        for (int i = n-1; i >= 1; i -= 2) {
            a[pt++] = i;
        }
        for (int i = 2; i <= n; i += 2) {
            a[pt++] = i;
        }
        for (int i = n-2; i >= 2; i -= 2) {
            a[pt++] = i;
        }
        a[pt++] = n;
    }
    for (int i = 0; i < pt; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}

