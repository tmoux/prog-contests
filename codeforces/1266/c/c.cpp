#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505;
int r, c;
int a[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> r >> c;
    if (r == 1 && c == 1) {
        cout << 0 << endl;
        return 0;
    }
    if (r == 1) {
        for (int j = 1; j <= c; j++) {
            cout << j+1 << ' ';
        }
        cout << '\n';
    }
    else if (c == 1) {
        for (int i = 1; i <= r; i++) {
            cout << i+1 << endl;
        }
    }
    else {
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                a[i][j] = i*(j+r);
                cout << a[i][j] << ' ';
            }
            cout << '\n';
        }
    }
}

