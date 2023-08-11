#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int str, intl, exp; cin >> str >> intl >> exp;
        str += exp;
        int ans = min(exp+1,max(0,(str-intl+1)/2));
        cout << ans << '\n';
    }
}
