#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    int n = s.size();
    vector<int> a;
    for (int i = 0; i < n; i++) {
        a.push_back(s[i]-'0');
        if (a[i] == 0 || a[i] == 8) {
            cout << "YES\n";
            cout << a[i] << '\n';
            return 0;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int tr = 10*a[i] + a[j];
            if (tr % 8 == 0) {
                cout << "YES\n";
                cout << tr << '\n';
                return 0;
            }
            for (int k = j+1; k < n; k++) {
                int tt = 100*a[i] + 10*a[j] + a[k];
                if (tt % 8 == 0) {
                    cout << "YES\n";
                    cout << tt << '\n';
                    return 0;
                }
            }
        }
    }
    cout << "NO\n";

    return 0;
}

