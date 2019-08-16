#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int sum = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    if (sum % 10 != 0) {
        cout << sum << '\n';
    }
    else {
        int mx = 0;
        for (int i = 0; i < n; i++) {
            mx = max(mx,(sum-a[i]) % 10 == 0 ? 0 : sum-a[i]);
        }
        cout << mx << '\n';
    }
}

