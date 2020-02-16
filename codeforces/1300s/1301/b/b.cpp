#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<int> adj;
        for (int i = 0; i < n; i++) {
            if (a[i] == -1) {
                if (i > 0 && a[i-1] != -1) {
                    adj.push_back(a[i-1]);
                }
                if (i < n-1 && a[i+1] != -1) {
                    adj.push_back(a[i+1]);
                }
            }
        }
        sort(adj.begin(),adj.end());
        if (adj.empty()) {
            cout << 0 << ' ' << 0 << '\n';
            continue;
        }
        int k = (adj[0]+adj.back())/2;
        for (int i = 0; i < n; i++) {
            if (a[i] == -1) a[i] = k;
        }
        int ans = 0;
        for (int i = 0; i < n-1; i++) {
            ans = max(ans,abs(a[i]-a[i+1]));
        }
        cout << ans << ' ' << k << endl;
    }
}

