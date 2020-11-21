#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> v;
    while (n) {
        v.push_back(n&1);
        n >>= 1;
    }
    reverse(v.begin(),v.end());
    int ans = 0;
    for (int i = 0, mult = 1; i < v.size(); i++, mult *= 2) {
        ans += v[i]*mult;
    }
    cout << ans << '\n';
}
