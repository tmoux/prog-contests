#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int y, b, r; cin >> y >> b >> r;
    int m = min(y,min(b-1,r-2));
    int ans = m + m + 1 + m + 2;
    cout << ans << '\n';

    return 0;
}

