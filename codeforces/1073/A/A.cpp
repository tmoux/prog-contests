#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string s; cin >> s;
    for (int i = 0; i < s.size() - 1; i++) {
        if (s[i] != s[i+1]) {
            cout << "YES\n";
            cout << s[i] << s[i+1] << '\n';
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}

