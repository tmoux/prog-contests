#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n; cin >> n;
    double ans = (n&1?n/2+1:n/2)/(double)(n);
    cout << fixed << setprecision(10) << ans << '\n';
}
