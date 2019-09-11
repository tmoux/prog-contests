#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, d, e; cin >> n >> d >> e;
    int ans = n;
    for (int i = 0; i < 500; i++) {
        int rem = n-5*i*e;
        if (rem < 0) break;
        ans = min(ans,rem%d);
    }
    cout << ans << '\n';
}

