#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s, t; cin >> s >> t;
    int ans = 99999;
    for (int i = 0; i + t.size() <= s.size(); i++) {
        int tr = 0;
        for (int j = 0; j < t.size(); j++) {
            if (s[i+j] != t[j]) tr++;
        }
        ans = min(ans,tr);
    }
    cout << ans << '\n';
}

