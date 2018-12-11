#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int r1, g1, b1, r2, g2, b2; cin >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
    r1 = sqrt(r1);
    g1 = sqrt(g1);
    b1 = sqrt(b1);
    r2 = sqrt(r2);
    g2 = sqrt(g2);
    b2 = sqrt(b2);
    bool dull = (r1 == r2 && g1 == g2 && b1 == b2);
    cout << (dull?"Dull":"Colourful") << '\n';
    return 0;
}

