#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string s; cin >> s;
    int bal = 0;
    for (char c: s) {
        if (c == '(') bal++;
        else bal--;
    }
    if (bal != 0) {
        cout << -1 << '\n';
        return 0;
    }
    bal = 0;
    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
        if (bal == 0 && s[i] == ')') {
            int cur = 0;
            int j = i;
            for (; j < s.size(); j++) {
                if (s[j] == '(') cur++;
                else cur--;
                if (cur == 0) break;
            }
            //cout << i << ' ' << j << endl;
            ans += j-i+1;
            i = j;
        }
        else {
            if (s[i] == '(') bal++;
            else bal--;
        }
    }
    cout << ans << '\n';
}
