#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int N;
int d[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    int mn = 2e9;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N-1; j++) {
            cin >> d[i][j];
            mn = min(mn,d[i][j]);
            if (j > 0) d[i][j] += d[i][j-1];
        }
    }
    if (mn >= 0) {
        int med = (N-1)/2-1;
        cout << "YES\n";
        for (int i = 0; i < N; i++) {
            cout << -d[i][med] << " \n"[i==N-1];
        }
        return 0;
    }
    else {
        //scream into the void
        cout << "AAA\n";
    }
}
