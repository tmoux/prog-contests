#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> z_function(const string& s) {
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

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        vector<int> z1 = z_function(s);
        reverse(s.begin(),s.end());
        vector<int> z2 = z_function(s);
        bool found = false;
        for (int i = 1; i < s.size(); i++) {
            bool poss = true;
            for (int j = i; j < s.size(); j += (i+1)) {
                int expect = s.size() - j;
                if (z1[j] != expect || z2[j] != expect) {
                    poss = false;
                    break;
                }
            }
            if (poss) {
                cout << "OK" << '\n';
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "MESSY" << '\n';
        }
        /*
        for (int i = 0; i < z1.size(); i++) {
            cout << z1[i] << ' ';
        }
        cout << '\n';
        for (int i = 0; i < z2.size(); i++) {
            cout << z2[i] << ' ';
        }
        cout << '\n';       
        */
    }

    return 0;
}

