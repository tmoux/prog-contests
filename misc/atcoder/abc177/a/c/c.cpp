#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    int sum = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ans = (ans+(1LL*a[i]*sum)%M)%M;
        sum = (sum+a[i]) % M;
    }
    cout << ans << '\n';
}
