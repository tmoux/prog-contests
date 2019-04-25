#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    string s; cin >> s;
    int c1 = 0, c2 = 0;
    for (char c: s) if (c == '.') c2++;
    int ans = 999999;
    for (char c: s) {
        ans = min(ans,c1+c2);
        if (c == '#') c1++;
        else c2--;
    }
    ans = min(ans,c1+c2);
    cout << ans << '\n';
}

