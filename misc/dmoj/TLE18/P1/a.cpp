#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    double d;
    double t = 0;
    while (cin >> d) {
        t += d;
        if (abs(t-floor(t)) < 1e-9) {
            cout << t << '\n';
        }
    }

}

