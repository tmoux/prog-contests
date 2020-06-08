#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int maxn = 1e5+5;
ld log_fac[2*maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    log_fac[0] = 0;
    for (int i = 1; i < 2*maxn; i++) {
        log_fac[i] = log_fac[i-1] + log2(i);
    }
    for (int q = 1; q <= t; q++) {
        cout << "Case #" << q << ": ";
        int W, H, L, U, R, D;
        cin >> W >> H >> L >> U >> R >> D;
        --L; --U; --R; --D;
        ld ans = 0;
        int x = L-1, y = D+1;
        auto calc = [&](int x, int y) {
            return log_fac[x+y] - log_fac[x] - log_fac[y] - (x+y);
        };
        while (x >= 0 && y < H) {
            ld lg = calc(x,y);
            ans += pow(2,lg);
            x--; y++;
        }
        x = R+1, y = U-1;
        while (x < W && y >= 0) {
            ld lg = calc(x,y);
            ans += pow(2,lg);
            x++; y--;
        }
        cout << fixed << setprecision(10) << ans << '\n';
    }
}
