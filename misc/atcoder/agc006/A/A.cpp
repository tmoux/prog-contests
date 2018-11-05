#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string s, t; cin >> s >> t;
    for (int i = 0; i < n; i++) {
        string r = s + t.substr(n-i);
        //cout << r << ' ' << r.substr(r.size()-n) << '\n';
        if (t == r.substr(r.size() - n)) {
            cout << n + i << '\n';
            return 0;
        }
    }
    cout << 2*n << '\n';

    return 0;
}

