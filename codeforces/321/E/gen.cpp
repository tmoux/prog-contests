#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int u[4005][4005];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    cout << n << ' ' << k << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cout << 0 << ' ';
                continue;
            }
            int r = (i<j?(rand() % 10):u[j][i]);
            u[i][j] = r;
            cout << r << ' ';
        }
        cout << '\n';
    }

    return 0;
}

