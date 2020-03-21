#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 55;
int a[maxn][maxn], d[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            if (a[i][j] > 1) d[i][j] = 2e9;
        }
    }
    for (int v = 1; v < k; v++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j] == v) {
                    for (int ii = 0; ii < n; ii++) {
                        for (int jj = 0; jj < n; jj++) {
                            if (a[ii][jj] == v+1) {
                                d[ii][jj] = min(d[ii][jj],d[i][j]+abs(i-ii)+abs(j-jj));
                            }
                        }
                    }
                }
            }
        }
    }
    int ans = 2e9;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == k) ans = min(ans,d[i][j]);
        }
    }
    cout << (ans < 2e8 ? ans : -1) << endl;
}

