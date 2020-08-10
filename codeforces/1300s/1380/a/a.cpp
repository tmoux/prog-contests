#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
        }
        for (int i = 1; i < n-1; i++) {
            int idx = -1;
            for (int j = 0; j < i; j++) {
                if (p[j] < p[i]) {
                    idx = j;
                    break;
                }
            }
            int idx2 = -1;
            for (int j = i+1; j < n; j++) {
                if (p[j] < p[i]) {
                    idx2 = j;
                    break;
                }
            }
            if (idx == -1 || idx2 == -1) {
                continue;
            }
            else {
                cout << "YES\n";
                cout << idx+1 << ' ' << i+1 << ' ' << idx2+1 << '\n';
                goto done;
            }
        }
        cout << "NO\n";
        done:;
    }
}
