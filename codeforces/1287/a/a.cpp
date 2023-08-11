#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string s; cin >> s;
        int cur = 0;
        int ans = 0;
        bool seen = false;
        for (int i = 0; i < s.size(); i++) {
            if (!seen) {
                if (s[i] == 'P') continue;
                else seen = true;
            }
            if (s[i] == 'P') cur++;
            else cur = 0;
            ans = max(ans,cur);
        }
        cout << ans << '\n';
    }
}

