#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5, M = 1e9+7, maxx = 1e6+6;
int n, a[maxn];

map<int,int> dp1, dp2;

void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}

int cnt[maxx];
int ans[maxx];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mx = max(mx,a[i]);
        for (int d = 1; d*d <= a[i]; d++) {
            if (a[i] % d == 0) {
                cnt[d]++;

                if (a[i]/d != d) {
                    cnt[a[i]/d]++;
                }
            }
        }
    }
    /*
    for (int i = 1; i <= n; i++) {
        cout << i << ": " << cnt[i] << '\n';
    }
    return 0;
    */
    int res = 0;
    for (int i = mx; i >= 2; i--) {
        ans[i] = mult(cnt[i],modexp(2,cnt[i]-1));
        //cout << i << ": " << ans[i] << '\n';
        for (int j = 2*i; j <= mx; j += i) {
            madd(ans[i],M-ans[j]);
        }
        //cout << i << ": " << ans[i] << '\n';
        madd(res,mult(i,ans[i]));
    }
    cout << res << '\n';
}
