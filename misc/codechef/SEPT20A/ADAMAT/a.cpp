#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 64;
int N;
int a[maxn][maxn];
int cv(int i, int j) {
    return i*N+j;
}
void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> a[i][j];
            --a[i][j];
        }
    }
    int ans = 0;
    for (int i = N-1; i >= 0; i--) {
        bool need = false;
        for (int j = 0; j <= i; j++) {
            if (a[i][j] != cv(i,j)) {
                assert(a[i][j] == cv(j,i) && a[j][i] == cv(i,j));
                need = true;
            }
        }
        if (need) {
            ans++;
            for (int ii = 0; ii <= i; ii++) {
                for (int jj = ii; jj <= i; jj++) {
                    swap(a[ii][jj],a[jj][ii]);
                }
            }
        }
        /*
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << a[i][j] << ' ';
            }
            cout << '\n';
        }
        */
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
