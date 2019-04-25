#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int a[2], b[2];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        a[ai&1]++;
    }
    for (int i = 0; i < m; i++) {
        int bi; cin >> bi;
        b[bi&1]++;
    }
    int ans = min(a[0],b[1]) + min(a[1],b[0]);
    cout << ans << '\n';

    return 0;
}

