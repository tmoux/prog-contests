#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    string s; cin >> s;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] > s[i+1]) {
            cout << "YES\n";
            cout << (i+1) << ' ' << (i+2) << '\n';
            return 0;
        }
    }
    cout << "NO\n";
}

