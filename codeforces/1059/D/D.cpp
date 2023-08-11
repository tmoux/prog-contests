#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

struct Point { int x, y; } A[100005];
int n;

bool check(ld y) {
    ld l = -1e50, r = 1e50;
    for (int i = 0; i < n; i++) {
        ld s = y*y-(y-(ld)(A[i].y))*(y-(ld)(A[i].y));
        //cout << y << ": " << s << '\n';
        if (s < 0) return false;
        ld sq = sqrt(s);
        l = max(l,(ld)(A[i].x)-sq);
        r = min(r,(ld)(A[i].x)+sq);
        //cout << y << ": " << l << ' ' << r << '\n';
    }
    //cout << y << ": " << l << ' ' << r << '\n';
    return l <= r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    bool pos = false, neg = false;
    for (int i = 0; i < n; i++) {
        cin >> A[i].x >> A[i].y;
        if (A[i].y > 0) pos = true;
        else neg = true;
    }
    if (pos && neg) {
        cout << "-1\n";
        return 0;
    }
    if (neg) {
        for (int i = 0; i < n; i++) {
            A[i].y *= -1;
        }
    }
    ld hi = 1e17, lo = 0;
    for (int i = 0; i < 2000; i++) {
        ld y = (hi+lo)/2;
        if (check(y)) hi = y;
        else lo = y;
    }
    cout << fixed << setprecision(10) << (hi+lo)/2 << '\n';


    return 0;
}

