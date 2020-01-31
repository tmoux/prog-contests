#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 55;
int n;
long double x[maxn], y[maxn];

long double sqr(long double x) { return x*x; }
long double dist(long double x1, long double y1, long double x2, long double y2) {
    return sqr(x1-x2) + sqr(y1-y2);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    long double X = 0, Y = 0, d, e;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        X += x[i];
        Y += y[i];
    }

    if (n == 2) {
        long double ans = sqrt(dist(x[0],y[0],x[1],y[1]))/2;
        cout << fixed << setprecision(10) << ans << '\n';
        return 0;
    }

    X /= n;
    Y /= n;
    long double P = 0.1;
    for (int i = 0; i < 30000; i++) {
        int f = 0;
        d = dist(X,Y,x[0],y[0]);
        for (int j = 1; j < n; j++) {
            e = dist(X,Y,x[j],y[j]);
            if (d < e) {
                d = e;
                f = j;
            }
        }
        X += (x[f]-X)*P;
        Y += (y[f]-Y)*P;
        P *= 0.999;
    }
    cout << fixed << setprecision(10) << sqrt(d) << '\n';
}

