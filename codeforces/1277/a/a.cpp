#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        set<int> s;
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            if (!(ai&1)) {
                s.insert(ai);
            }
        }
        int ans = 0;
        while (!s.empty()) {
            auto t = *s.rbegin();
            s.erase(prev(s.end()));
            if (t % 2 == 0 && (t/2)%2 == 0) {
                s.insert(t/2);
            }
            ans++;
        }
        cout << ans << '\n';
    }
}

