#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int f(ll a, ll b) {
    int res = 0;
    if (a < b) return 1e9;
    while (a > b) {
        b *= 2;
        res++;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("folding.in","r",stdin);
    freopen("folding.out","w",stdout);
    int W, H, w, h; cin >> W >> H >> w >> h;
    int ans = min(f(W,w)+f(H,h),f(W,h)+f(H,w));
    cout << (ans >= 1e9 ? -1 : ans) << '\n';
}

