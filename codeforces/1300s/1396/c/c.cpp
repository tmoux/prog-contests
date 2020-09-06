#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//laser: only use initially
//AWP: only for the boss
//strategy 1: all pistol
//         2: laser, then come back and pistol
//         3: pistol, then AWP for the boss
//start with (d-1)*n for all forward 

const int maxn = 1e6+6;
int n;
ll d, r1, r2, r3;
ll a[maxn];

ll dp1[maxn][2], dp2[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    cin >> r1 >> r2 >> r3 >> d;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            dp1[i][0] = a[i]*r1+r3;
            dp1[i][1] = min(r2,(a[i]+1)*r1)+2*d+r1;
        }
        else {
            dp1[i][0] = min(a[i]*r1+r3 + min(dp1[i-1][0],dp1[i-1][1]),
                            min(r2,(a[i]+1)*r1)+r1 + dp1[i-1][1]);
            dp1[i][1] = min(r2,(a[i]+1)*r1)+r1 + min(dp1[i-1][0],dp1[i-1][1])+2*d;
        }
    }
    for (int i = n-1; i >= 0; i--) {
        if (i == n-1) {
            dp2[i] = min(min(r2,(a[i]+1)*r1)+2*d+r1,
                         a[i]*r1+r3);
        }
        else {
            dp2[i] = min(min(r2,(a[i]+1)*r1)+r1,
                         a[i]*r1+r3)+d+dp2[i+1];
        }
    }
    /*
    for (int i = 0; i < n; i++) {
        cout << dp1[i][0] << ' ';
    }
    cout << '\n';
    for (int i = 0; i < n; i++) {
        cout << dp1[i][1] << ' ';
    }
    cout << '\n';
    for (int i = 0; i < n; i++) {
        cout << dp2[i] << ' ';
    }
    cout << '\n';
    */
    ll ans = 1e18;
    for (int i = 0; i < n; i++) {
        ans = min(ans,dp1[i][0]+dp2[i+1]+1LL*(n-1)*d);
        ans = min(ans,dp1[i][1]+dp2[i+1]+1LL*(n-1)*d);
    }
    ans = min(ans,dp2[0]+1LL*(n-1)*d);
    cout << ans << '\n';
}
