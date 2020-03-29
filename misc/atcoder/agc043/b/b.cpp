#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+5;
int n, a[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        char c; cin >> c;
        a[i] = c-'0'-1;
    }
    int par = 0;
    for (int i = 0; i < n; i++) {
        if (((n-1)|i) == n-1) {
            par ^= (a[i]%2);
        }
    }
    if (par) {
        cout << 1 << '\n';
    }
    else {
        for (int i = 0; i < n; i++) {
            if (a[i] == 1) {
                cout << 0 << '\n';
                return 0;
            }
        }
        for (int i = 0; i < n; i++) {
            a[i] /= 2;
        }
        par = 0;
        for (int i = 0; i < n; i++) {
            if (((n-1)|i) == n-1) {
                par ^= (a[i]%2);
            }
        }
        cout << 2*par << '\n';
    }
}
