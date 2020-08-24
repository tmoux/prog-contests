#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 26;
ll grid[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    for (int i = 1; i < n; i += 2) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = 1LL<<(i+j);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }
    int q; cin >> q;
    while (q--) {
        ll k; cin >> k;
        int x = 0, y = 0;
        vector<pair<int,int>> ans = {{x,y}};
        for (int i = 1; i <= 2*(n-1); i++) {
            ll f = k&(1LL<<i);    
            if ((x % 2 == 0) ^ (f > 0)) {
                y++;
            }
            else x++;

            ans.push_back({x,y});
        }
        assert(x == y && y == n-1);
        for (auto p: ans) {
            cout << p.first+1 << ' ' << p.second+1 << endl;
        }
    }
}
