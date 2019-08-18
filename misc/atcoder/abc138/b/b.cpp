#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    ld den = 0;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        den += (ld)(1.0)/(ld)(ai);
    }
    den = (ld)(1.0)/den;
    cout << fixed << setprecision(10) << den << '\n';

}

