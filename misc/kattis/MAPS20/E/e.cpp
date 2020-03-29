#include <bits/stdc++.h>
using namespace std;
using ll = long long;

double round(double x) {
    return floor(x*100+0.5)/100;
}

void solve() {
    double A, B;
    int T;
    cin >> A >> B >> T;
    for (double d = A; d <= B; d += 0.01) {
        double calc = round(d*(1+T/100.0));
        printf("%.2f: %.2f\n",d,calc);
    }
    
}

int main() {
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
