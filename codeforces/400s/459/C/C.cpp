#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int ans[1005][1005];
int cnt[1005][1005];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k, d; cin >> n >> k >> d;
    bool poss = false;
    ll tmp = 1;
    for (int i = 0; i < d; i++) {
        tmp *= k;
        if (tmp >= n) {
            poss = true;
            break;
        }
    }
    if (!poss) {
        cout << -1 << '\n';
    }
    else {
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < d; j++) ans[i][j] = ans[i-1][j];
            for (int j = d - 1; j >= 0; j--) {
                ans[i][j] = (ans[i][j] + 1) % k;
                if (ans[i][j]) break;
            }
        }
        //ouput
        for (int i = 0; i < d; i++) {
            for (int j = 0; j < n; j++) {
                cout << ans[j][i] + 1 << ' ';
            }
            cout << '\n';
        }
    }

    return 0;
}

