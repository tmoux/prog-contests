#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int g[2][maxn];

int main() {
    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < n; j++) {
                char c; cin >> c;
                int t = c-'0';
                g[i][j] = t <= 2 ? 1 : 2;
                //1 = straight, 2 = 90 degree bend
            }
        }
        int row = 0;
        int j = 0;
        int dir = 0; //0 = from left, 1 = from up/down
        bool poss = true;
        while (j < n) {
            if (dir == 0) {
                if (g[row][j] == 1) {
                    j++;
                }
                else {
                    row ^= 1;
                    dir = 1;
                }
            }
            else {
                if (g[row][j] == 1) {
                    poss = false;
                    break;
                }
                else {
                    j++;
                    dir = 0;
                }
            }
        }
        if (poss && j == n && row == 1) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
}

