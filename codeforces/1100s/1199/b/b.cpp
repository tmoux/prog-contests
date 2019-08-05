#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll H, L; cin >> H >> L;
    ld D = (ld)(L*L-H*H)/(ld)(2*H);
    cout << fixed << setprecision(10) << D << '\n';

}

