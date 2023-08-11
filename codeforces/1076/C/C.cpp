#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


void solve() {
    int d; cin >> d;
    if (d*d-4*d < 0) {
        cout << "N\n";
        return;
    }
    double a = (d + sqrt(d*d-4*d))/2.0;
    double b = d-a;
    cout << fixed << setprecision(10) << "Y " << a << ' ' << b << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t; while (t--) solve();
    return 0;
}

