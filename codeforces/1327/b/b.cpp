#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<vector<int>> v(n+1,vector<int>());
        for (int i = 1; i <= n; i++) {
            int k; cin >> k;
            while (k--) {
                int ai; cin >> ai;
                v[i].push_back(ai);
            }
        }
        vector<bool> taken(n+1,false);
        vector<bool> good(n+1,false);
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            for (int j: v[i]) {
                if (!taken[j]) {
                    taken[j] = true;
                    good[i] = true;
                    ++cnt;
                    break;
                }
            }
        }
        if (cnt == n) {
            cout << "OPTIMAL\n";
        }
        else {
            int i = 1;
            for (; i <= n; i++) {
                if (!good[i]) {
                    break;
                }
            }
            int j = 1;
            for (; j <= n; j++) {
                if (!taken[j]) {
                    break;
                }
            }
            cout << "IMPROVE\n" << i << ' ' << j << '\n';
        }
    }
}

