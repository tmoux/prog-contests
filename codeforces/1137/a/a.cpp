#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) begin(x),end(x)

const int maxn = 1005;
int a[maxn][maxn];
vector<int> rows[maxn], cols[maxn];
int n, m;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            rows[i].push_back(a[i][j]);
            cols[j].push_back(a[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        sort(all(rows[i]));
        rows[i].erase(unique(all(rows[i])),rows[i].end());
    }
    for (int i = 0; i < m; i++) {
        sort(all(cols[i]));
        cols[i].erase(unique(all(cols[i])),cols[i].end());
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            auto it = lower_bound(all(rows[i]),a[i][j]);
            auto it2 = lower_bound(all(cols[j]),a[i][j]);
            int ans = max(distance(rows[i].begin(),it),distance(cols[j].begin(),it2)) +
                      max(distance(it,rows[i].end()),distance(it2,cols[j].end()));
            cout << ans << ' ';
        }
        cout << '\n';
    }
}

