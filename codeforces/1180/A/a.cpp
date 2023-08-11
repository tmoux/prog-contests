#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    int ans = 1;
    for (int i = 2; i <= n; i++) {
        ans += (i-1)*4;
    }
    cout << ans << '\n';
}

