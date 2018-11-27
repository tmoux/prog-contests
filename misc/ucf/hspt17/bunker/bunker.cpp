#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

double dist(double a, double b, int r) {
    double theta = min(abs(a-b),360-abs(a-b));
    return 1.0*theta*(double)r*3.14159265/180.0;
}

void solve(int t) {
    int rr, c; cin >> rr >> c;
    vector<double> homes(c);
    for (int i = 0; i < c; i++) cin >> homes[i];
    double ans = 1e18;
    for (int i = 0; i < c; i++) {
        double r = 0.0;
        for (int j = 0; j < c; j++) {
            r += dist(homes[i],homes[j],rr);
        }
        //cout << i << ": " << r << '\n';
        ans = min(ans,r);
    }
    printf("Tree #%d: %3f\n",t,ans);
}

int main()
{
    int t; cin >> t;
    for (int i = 1; i <= t; i++) solve(i);

    return 0;
}

