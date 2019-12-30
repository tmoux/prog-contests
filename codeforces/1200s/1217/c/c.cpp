#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int n = s.size();
        vector<int> nxt(n);
        for (int i = n-1; i >= 0; i--) {
            if (s[i] == '1') nxt[i] = i;
            else nxt[i] = i==n-1?n:nxt[i+1];
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int curr = 0;
            for (int j = nxt[i]; j < min(n,nxt[i]+20); j++) {
                curr *= 2;
                if (s[j] == '1') curr++;
                int len = j-i+1;
                if (len == curr) ans++;
            }
        }
        cout << ans << '\n';
    }
}

