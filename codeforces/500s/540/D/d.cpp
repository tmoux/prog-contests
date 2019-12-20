#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int maxn = 105;
int R, S, P;

ld dp[maxn][maxn][maxn];

ld rf(int r, int s, int p) {
    if (r < 0 || s < 0 || p < 0) return 0;
    if (r == 0) return 0;
    if (r > 0 && s == 0 && p == 0) {
        return 1;
    }
    ld& res = dp[r][s][p];
    if (res != -1) return res;
    res = 0;
    int tot = r+s+p;
    int den = tot*(tot-1)-r*(r-1)-s*(s-1)-p*(p-1);
    //rs
    res += (ld)(2*r*s)/den*rf(r,s-1,p);
    //sp
    res += (ld)(2*s*p)/den*rf(r,s,p-1);
    //rp
    res += (ld)(2*r*p)/den*rf(r-1,s,p);
    //cout << r << ' ' << s << ' ' << p << ": " << res << '\n';
    return res;
}

ld sf(int r, int s, int p) {
    if (r < 0 || s < 0 || p < 0) return 0;
    if (s == 0) return 0;
    if (s > 0 && r == 0 && p == 0) {
        return 1;
    }
    ld& res = dp[r][s][p];
    if (res != -1) return res;
    res = 0;
    int tot = r+s+p;
    int den = tot*(tot-1)-r*(r-1)-s*(s-1)-p*(p-1);
    //rs
    res += (ld)(2*r*s)/den*sf(r,s-1,p);
    //sp
    res += (ld)(2*s*p)/den*sf(r,s,p-1);
    //rp
    res += (ld)(2*r*p)/den*sf(r-1,s,p);
    //cout << r << ' ' << s << ' ' << p << ": " << res << '\n';
    return res;
}

ld pf(int r, int s, int p) {
    if (r < 0 || s < 0 || p < 0) return 0;
    if (p == 0) return 0;
    if (p > 0 && r == 0 && s == 0) {
        return 1;
    }
    ld& res = dp[r][s][p];
    if (res != -1) return res;
    res = 0;
    int tot = r+s+p;
    int den = tot*(tot-1)-r*(r-1)-s*(s-1)-p*(p-1);
    //rs
    res += (ld)(2*r*s)/den*pf(r,s-1,p);
    //sp
    res += (ld)(2*s*p)/den*pf(r,s,p-1);
    //rp
    res += (ld)(2*r*p)/den*pf(r-1,s,p);
    //cout << r << ' ' << s << ' ' << p << ": " << res << '\n';
    return res;
}

void reset() {
    for (int i = 0; i < maxn; i++) {
        for (int j = 0; j < maxn; j++) {
            for (int k = 0; k < maxn; k++) {
                dp[i][j][k] = -1;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> R >> S >> P;
    cout << fixed << setprecision(10);
    reset();
    ld rock = rf(R,S,P);
    reset();
    ld scissors = sf(R,S,P);
    reset();
    ld paper = pf(R,S,P);
    cout << rock << ' ' << scissors << ' ' << paper << '\n';
}

