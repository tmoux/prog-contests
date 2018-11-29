#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int ceil(int a, int b) {
    return a%b==0?a/b:a/b+1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin>> t;
    while (t--) {
        int n, x, y, d; cin >> n >> x >> y >> d;
        if (abs(x-y) % d == 0) {
            cout << abs(x-y)/d << '\n';
            continue;
        }
        else {
            int ans = 999999999;
            if ((y-1) % d == 0) {
                int to1 = ceil(x-1,d);
                ans = min(ans,to1+(y-1)/d);
            }
            if ((n-y) % d == 0) {
                int to1 = ceil(n-x,d);
                ans = min(ans,to1+(n-y)/d);
            }
            if (ans == 999999999) {
                cout << -1 << '\n';
            }
            else {
                cout << ans << '\n';
            }
        }
    }

    return 0;
}

