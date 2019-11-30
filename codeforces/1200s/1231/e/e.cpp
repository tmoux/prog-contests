#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int n;
string s, t;

int solve() {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int cur = i;
        for (int j = 0; j < n; j++) {
            if (cur < n && s[j] == t[cur]) {
                cur++;
            }
        }
        ans = max(ans,cur-i);
    }
    return n - ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        cin >> n;
        cin >> s >> t;
        map<char,int> mp1, mp2;
        for (char c: s) {
            mp1[c]++;
        }
        for (char c: t) {
            mp2[c]++;
        }
        bool poss = true;
        for (auto p: mp1) {
            if (mp2[p.first] != p.second) {
                poss = false;
                break;
            }
        }
        if (!poss) {
            cout << -1 << '\n';
        }
        else {
            cout << solve() << '\n';
        }
    }
}

