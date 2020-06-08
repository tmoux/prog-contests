#include <bits/stdc++.h>
using namespace std;
using ll = long long;

set<int> intersect(set<int> a, set<int> b) {
    set<int> ret;
    for (auto i: a) if (b.count(i)) ret.insert(i);
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        vector<vector<int>> v(9,vector<int>(9));
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char c; cin >> c;
                v[i][j] = c-'0';
            }
        }
        auto f = [&v](int a, int b) {
            //cout << a << ' ' << b << endl;
            set<int> row, col, block;
            for (int j = 0; j < 9; j++) {
                if (j == b) continue;
                row.insert(v[a][j]);
            }
            for (int j = 0; j < 9; j++) {
                if (j == a) continue;
                col.insert(v[j][b]);
            }
            int b1 = a/3, b2 = b/3;
            for (int x = 0; x < 9; x++) {
                for (int y = 0; y < 9; y++) {
                    if (x/3 == b1 && y/3 == b2) {
                        if (x == a && y == b) continue;
                        block.insert(v[x][y]);
                    }
                }
            }
            auto ins = intersect(row,intersect(col,block));
            assert(!ins.empty());
            v[a][b] = *ins.begin();
        };
        for (int row = 0, col = 0; row < 9; row++, col = (col+3)%9) {
            if (row == 3 || row == 6) col = (col+1)%9;
            f(row,col);
        }
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << v[i][j];
            }
            cout << '\n';
        }
    }
}
