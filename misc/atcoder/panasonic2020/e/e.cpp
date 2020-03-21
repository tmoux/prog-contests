#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005;
vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int solve(const string& a, const string& b, const string& c) {
    int ans = 3*maxn;
    for (int i = 0; i <= a.size(); i++) {
        bool poss = true;
        string t = a;
        for (int j = 0; j < b.size(); j++) {
            if (i+j >= a.size()) {
                t += b[j];
            }
            else if (a[i+j] == '?') {
                t[i+j] = b[j];
            }
            else if (b[j] == '?') {
                continue;
            }
            else if (a[i+j] == b[j]) {
                continue;
            }
            else {
                poss = false;
                break;
            }
        }
        if (!poss) continue;

    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string a, b, c; cin >> a >> b >> c;
    int ans = solve(a,b,c);
    //cout << ans << '\n';
    ans = min(ans,solve(a,c,b));
    //cout << ans << '\n';
    ans = min(ans,solve(b,a,c));
    //cout << ans << '\n';
    ans = min(ans,solve(b,c,a));
    //cout << ans << '\n';
    ans = min(ans,solve(c,a,b));
    //cout << ans << '\n';
    ans = min(ans,solve(c,b,a));
    cout << ans << '\n';
}

