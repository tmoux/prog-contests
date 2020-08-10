#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int N, Q;

int h[maxn], a[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) {
        cin >> h[i];
    }
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }
    while (Q--) {
        int t, b, c; cin >> t >> b >> c;
        if (t == 1) {
            a[b] = c;
        }
        else {
            int cur_height = h[c];
            ll ans = a[c];
            bool poss = true;
            if (c <= b) {
                for (int i = c; i <= b; i++) {
                    if (h[i] > cur_height) {
                        cur_height = h[i];
                        ans += a[i];
                    }
                    if (cur_height >= h[b] && i < b) {
                        poss = false;
                        break;
                    }
                }
            }
            else {
                for (int i = c; i >= b; i--) {
                    if (h[i] > cur_height) {
                        cur_height = h[i];
                        ans += a[i];
                    }
                    if (cur_height >= h[b] && i > b) {
                        poss = false;
                        break;
                    }
                }
            }
            if (!poss) {
                cout << -1 << '\n';
            }
            else {
                //cout << "cur height = " << cur_height << endl;
                cout << ans << '\n';
            }
        }
    }
}
