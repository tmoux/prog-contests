#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) begin(x),end(x)

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        vector<vector<int>> grid(n,vector<int>(n,0));
        vector<int> row(n,0), col(n,0);
        auto add = [&grid,&row,&col,&k](int i, int j) {
            if (k > 0) {
                grid[i][j] = 1;
                row[i]++;
                col[j]++;
                k--;
            }
        };
        int i = 0, j = 0;
        while (k) {
            add(i,j);
            i++;
            j = (j+1)%n;
            if (i == n) {
                i = 0;
                j = (j+1)%n;
            }
        }
        auto sqr = [](int x) {
            return x*x;
        };
        int ans = sqr(*max_element(all(row))-*min_element(all(row)));
        ans    += sqr(*max_element(all(col))-*min_element(all(col)));
        cout << ans << '\n';
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << grid[i][j];
            }
            cout << '\n';
        }
    }
}
