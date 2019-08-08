#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    int ans = 2e9;
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        if (k % ai == 0) {
            ans = min(ans,k/ai);
        }
    }
    cout << ans << '\n';
}

