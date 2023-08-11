#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<bool> p(n,false);
        for (int i = 0; i < m; i++) {
            int pi; cin >> pi;
            p[pi-1] = true;
        }
        vector<int> tr;
        vector<int> curr;
        for (int i = 0; i < n; i++) {
            curr.push_back(a[i]);
            if (!p[i]) {
                sort(curr.begin(),curr.end());
                for (auto j: curr) {
                    tr.push_back(j);
                }
                curr.clear();
            }
        }
        sort(a.begin(),a.end());
        cout << ((a == tr) ? "YES" : "NO") << endl;
    }
}

