#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int n, x;

int mod2(int x) {
    return ((x%2)+2)%2;
}

bool same(int a, int b) {
    return mod2(a) == mod2(b);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n >> x;
        vector<int> a(n);
        int numSame = 0;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] == x) numSame++;
            sum += a[i]-x;
        }
        if (numSame == n) {
            cout << 0 << '\n';
        }
        else {
            if (sum == 0) {
                cout << 1 << '\n';
            }
            else {
                if (numSame > 1) {
                    cout << 1 << '\n';
                }
                else if (numSame == 1) {
                    bool found = false;
                    for (int i = 0; i < n; i++) {
                        if (same(x,a[i]+sum)) {
                            cout << 1 << '\n';
                            found = true;
                            break;
                        }
                    }
                    if (!found) cout << 2 << '\n';
                }
                else {
                    cout << 2 << '\n';
                }
            }
        }
    }
}
