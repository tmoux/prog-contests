#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    string s; cin >> s;
    sort(s.begin(),s.end());
    if (s[0] == s[s.size()-1]) {
        cout << -1 << '\n';
    }
    else {
        cout << s << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t; while (t--) solve();

    return 0;
}

