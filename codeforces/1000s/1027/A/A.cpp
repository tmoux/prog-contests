#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    int n; string s; cin >> n >> s;
    bool is = true;
    for (int i = 0; i < n/2; i++) {
        if (!(s[i] == s[n-1-i] || (abs(s[i]-s[n-1-i]) == 2))) {
            is = false;
            break;
        }
    }
    cout << (is ? "YES" : "NO") << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();

    return 0;
}
	

