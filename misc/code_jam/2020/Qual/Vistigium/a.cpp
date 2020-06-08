#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int a[105][105];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cout << "Case #" << qq << ": ";
        int n; cin >> n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> a[i][j];
            }
        }
        int trace = 0;
        for (int i = 1; i <= n; i++) {
            trace += a[i][i];
        }
        int r = 0;
        for (int i = 1; i <= n; i++) {
            set<int> s;
            for (int j = 1; j <= n; j++) {
                s.insert(a[i][j]);
            }
            if (s.size() != n) r++;
        }
        int c = 0;
        for (int i = 1; i <= n; i++) {
            set<int> s;
            for (int j = 1; j <= n; j++) {
                s.insert(a[j][i]);
            }
            if (s.size() != n) c++;
        }
        cout << trace << ' ' << r << ' ' << c << '\n';
    }
}

