#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5;
int q;
int a[maxn];
const int BLK = 350; //seems to be about optimal

ll c[BLK+5][BLK+5];
ll cnt[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> q;
    while (q--) {
        int t, x, y; cin >> t >> x >> y;
        if (t == 1) {
            cnt[x] -= a[x];
            for (int i = 1; i < BLK; i++) {
                c[i][x%i] -= a[x];
            }
            a[x] += y;
            cnt[x] += a[x];
            for (int i = 1; i < BLK; i++) {
                c[i][x%i] += a[x];
            }
        }
        else {
            if (x < BLK) {
                cout << c[x][y] << '\n';
            }
            else {
                ll ans = 0;
                for (; y <= 500000; y += x) {
                    ans += cnt[y];
                }
                cout << ans << '\n';
            }
        }
    }
}

