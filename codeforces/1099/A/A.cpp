#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int w, h, u1, d1, u2, d2;
    cin >> w >> h >> u1 >> d1 >> u2 >> d2;
    for (int i = h; i >= 1; i--) {
        w += i;
        if (i == d1) w -= u1;
        else if (i == d2) w -= u2;
        w = max(w,0);
    }
    cout << w << '\n';

    return 0;
}

