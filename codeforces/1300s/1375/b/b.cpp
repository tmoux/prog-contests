#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> a(n,vector<int>(m));
        auto valid = [&n,&m](int i, int j) {
            return 0 <= i && i < n && 0 <= j && j < m;
        };
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int c; cin >> c;
                a[i][j] = c;
            }
        }
        bool poss = true;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int cnt = 0;
                for (int k = 0; k < 4; k++) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (valid(ni,nj)) cnt++;
                }
                if (a[i][j] > cnt) {
                    poss = false;
                    break;
                }
                else {
                    a[i][j] = cnt;
                }
            }
        }
        if (!poss) {
            cout << "NO\n";
        }
        else {
            cout << "YES\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << a[i][j] << ' ';
                }
                cout << '\n';
            }
        }
    }
}

