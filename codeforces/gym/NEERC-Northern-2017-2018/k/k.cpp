#include <bits/stdc++.h>
using namespace std;
using ll = long long;

char grid[105][105];
int h, w, n;
void ans(int x, int y) {
    for (int cnt = 0, i = 1; cnt < x; i += 2, cnt++) {
        for (int j = 0; j < w; j++) {
            grid[i][j] = '#';
        }
    }
    for (int cnt = 0, j = 1; cnt < y; j += 2, cnt++) {
        for (int i = 0; i < h; i++) {
            grid[i][j] = '#';
        }
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cout << grid[i][j];
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("kotlin.in","r",stdin); freopen("kotlin.out","w",stdout);
    cin >> h >> w >> n;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            grid[i][j] = '.';
        }
    }
    for (int i = 1; i*i <= n; i++) {
        if (n % i == 0) {
            if (i <= (h+1)/2 && n/i <= (w+1)/2) {
                ans(i-1,n/i-1);
                return 0;
            }
            else if (n/i <= (h+1)/2 && i <= (w+1)/2) {
                ans(n/i-1,i-1);
                return 0;
            }
        }
    }
    cout << "Impossible\n";
}

