#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int p, q, s; cin >> p >> q >> s;
    int lc = p*q / __gcd(p,q);
    cout << (lc <= s ? "yes" : "no") << '\n';

    return 0;
}

