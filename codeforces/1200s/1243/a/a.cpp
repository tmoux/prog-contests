#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(),a.end(),greater<int>());
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans,min(i+1,a[i]));
        }
        cout << ans << '\n';
    }
}

