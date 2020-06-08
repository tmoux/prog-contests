#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll ch[505][505];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cout << "Case #" << qq << ":\n";
        ll n; cin >> n;
        if (false /*n <= 1000*/) {
            if (n == 1) {
                cout << "1 1\n";   
                continue;
            }
            int r = 0, k = 0;
            cout << "1 1\n";
            n--; r++; k++;
            while (n-r >= 0) {
                cout << (r+1) << ' ' << (k+1) << '\n';
                n -= r;
                r++;
            }
            while (n > 0) {
                if (k == 1) {
                    k--;
                    r--;
                }
                else {
                    r++;
                }
                cout << (r+1) << ' ' << (k+1) << '\n';
                n--;
            }
        }
        else {
            ch[0][0] = 1;
            for (int i = 1; i <= 500; i++) {
                ch[i][0] = 1;
                for (int j = 1; j <= i; j++) {
                    ch[i][j] = max(1LL,ch[i-1][j-1] + ch[i-1][j]);
                }
            }

            int r = 0, k = 0;
            cout << "1 1\n";
            n--;
            while (n > 0) {
                int nk = k+1;
                if (nk > (r+2)/2) nk--;
                ll sum = 0;
                for (int i = 0; i <= nk; i++) {
                    sum += ch[r+1][i];
                }
                //cout << "sum = " << sum << endl;
                //cout << n << ' ' << ch[r][k-1] << endl;
                assert(sum >= 0);
                if (sum <= n) {
                    r++;
                    k = nk;
                }
                else if (sum-ch[r+1][nk] <= n && nk-1 >= k) {
                    r++;
                    k = nk-1;
                }
                else if (ch[r][k-1] <= n) {
                    assert(k > 0);
                    k--;
                }
                else {
                    //cout << (r+1) << ' ' << (k+1) << endl;
                    assert(false);
                }
                n -= ch[r][k];
                cout << (r+1) << ' ' << (k+1) << endl;
                cout << "n = " << n << endl;
            }
            assert(n == 0);
        }
    }
}

