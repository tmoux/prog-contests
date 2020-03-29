#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    int ans = n*(n-1)/2;
    ans += m*(m-1)/2;
    cout << ans << '\n';
}

