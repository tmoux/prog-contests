#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const double PI = 3.14159265358979323846;
const double INF = 1e18;
int n, r;

double dist(int a, int b) {
    double theta = min(abs(a-b),n-abs(b-a))/(double)(n) * 2 * PI;
    return r*sqrt(2.0*(1-cos(theta)));
}

string s;
int rcnt, gcnt, bcnt;

double dp[1<<16][16];

void amin(double& a, double b) {
    a = min(a,b);
}

double f(int mask, int i) {
    mask |= (1 << i);
    //cout << mask << ' ' << i << '\n';
    if ((mask + 1) == (1 << n)) return 0;
    if (dp[mask][i] > 0) return dp[mask][i];
    dp[mask][i] = INF;
    int rr = rcnt, gg = gcnt, bb = bcnt;
    //cout << rr << ' ' << gg << ' ' << bb << '\n';
    for (int j = 0; j < n; j++) {
        if (mask & (1 << j)) {
            //cout << j << ": " << s[j] << '\n';
            char c = s[j];
            (c=='R'?rr:c=='G'?gg:bb)--;
        }
    }
    //cout << rr << ' ' << gg << ' ' << bb << '\n';
    if (rr > 0) {
        for (int j = 0; j < n; j++) {
            if (!(mask & (1 << j)) && s[j] == 'R') {
                amin(dp[mask][i],f(mask,j)+dist(i,j));
            }
        }
    }
    else if (gg > 0) {
        for (int j = 0; j < n; j++) {
            if (!(mask & (1 << j)) && s[j] == 'G') {
                amin(dp[mask][i],f(mask,j)+dist(i,j));
            }
        }
    }
    else if (bb > 0) {
        for (int j = 0; j < n; j++) {
            if (!(mask & (1 << j)) && s[j] == 'B') {
                amin(dp[mask][i],f(mask,j)+dist(i,j));
            }
        }
    }
    return dp[mask][i];
}

int main()
{
    int t; cin >> t;
    
    for (int a = 1; a <= t; a++) {
        rcnt = 0;
        gcnt = 0;
        bcnt = 0;
        cin >> n >> r;
        cin >> s;
        for (char c: s) {
            (c=='R'?rcnt:c=='G'?gcnt:bcnt)++;
        }
        double ans = INF;
        for (int i = 0; i < (1 << 16); i++) {
            for (int j = 0; j < 16; j++) {
                dp[i][j] = -1;
            }
        }
        if (rcnt > 0) {
            for (int i = 0; i < n; i++) {
                if (s[i] == 'R') {
                    amin(ans,f(0,i));
                }
            }
        }
        else if (gcnt > 0) {
            for (int i = 0; i < n; i++) {
                if (s[i] == 'G') {
                    amin(ans,f(0,i));
                }
            }
        }
        else if (bcnt > 0) {
            for (int i = 0; i < n; i++) {
                if (s[i] == 'B') {
                    amin(ans,f(0,i));
                }
            }
        }
        cout << fixed << setprecision(3) << "Scenario #" << a << ": " << ans << '\n';
    }

    return 0;
}

