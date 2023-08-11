#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int res = 0, n; cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        res = max(res,x+y);
    }
    cout << res << '\n';

    return 0;
}

