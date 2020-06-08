#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        multiset<int> ms;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] != 0) ms.insert(a[i]);
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        bool poss = true;
        for (int i = n-1; i >= 0; i--) {
            if (a[i] != 0) {
                auto it = ms.find(a[i]);
                ms.erase(it);
            }
            if (a[i] == b[i]) continue;
            else if (a[i] < b[i]) {
                if (!ms.empty() && *ms.rbegin() == 1) {

                }
                else poss = false;
            }
            else if (a[i] > b[i]) {
                if (!ms.empty() && *ms.begin() == -1) {

                }
                else poss = false;
            }
        }
        cout << (poss ? "YES" : "NO") << '\n';
    }
}

