#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string s; cin >> s;
        int f = s.find('8');
        if (f != string::npos && n-f >= 11) {
            cout << "YES\n";
        }
        else cout << "NO\n";
    }

}

