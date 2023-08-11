#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        int bad = -1e5+5;
        int done = 1e5+5;
        int diff = bad;
        bool poss = true;
        for (int i = 0; i < n; i++) {
            if (b[i] < a[i]) {
                poss = false;
                break;
            }
            if (diff == done) {
                if (b[i]-a[i] == 0) continue;
                else {
                    poss = false;
                    break;
                }
            }
            else if (diff != bad) {
                if (b[i]-a[i] == diff) {
                    continue;
                }
                else if (b[i]-a[i] == 0) {
                    diff = done;
                }
                else {
                    poss = false;
                    break;
                }
            }
            else {
                if (b[i]-a[i] == 0) continue;
                else {
                    diff = b[i]-a[i];
                }
            }
        }
        cout << (poss?"YES":"NO") << '\n';
    }
}

