#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//abacaba
string S = "abacaba";
int cnt(string t) {
    int res = 0;
    for (int i = 0; i+7 <= t.size(); i++) {
        res += (t.substr(i,7) == S);
    }
    return res;
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string s; cin >> s;
        for (int i = 0; i+7 <= n; i++) {
            string t = s;
            for (int j = 0; j < 7; j++) {
                if (t[i+j] == '?' || t[i+j] == S[j]) {
                    t[i+j] = S[j];
                }
            }
            for (int j = 0; j < n; j++) {
                if (t[j] == '?') t[j] = 'z';
            }
            //cout << t << ' ' << cnt(t) << '\n';
            if (cnt(t) == 1) {
                cout << "Yes\n";
                cout << t << '\n';
                goto done;
            }
        }
        cout << "No\n";
        done:;
    }
}
