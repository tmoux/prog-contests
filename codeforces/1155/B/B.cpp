#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    string s; cin >> s;
    vector<bool> bad(n);
    int m = n - 11;
    int i = 0, j = 0;
    for (int a = 0; a < m; a++) {
        if (a%2 == 0) {
            //find first thing that isn't 8
            while (i < n && s[i] == '8') i++;
            if (i < n) bad[i] = true;
            i++;
        }
        else {
            while (j < n && s[j] != '8') j++;
            if (j < n) bad[j] = true;
            else {
                cout << "NO" << '\n'; //killed all 8's
                return 0;
            }
            j++;
        }
        /*
        for (int k = 0; k < n; k++) {
            cout << bad[k] << ' ';
        }
        cout << '\n';
        for (int k = 0; k < n; k++) {
            cout << s[k] << ' ';
        }
        cout << "\n\n";
        */
    }
    for (int i = 0; i < n; i++) {
        if (!bad[i]) {
            if (s[i] == '8') {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
            return 0;
        }
    }
}

