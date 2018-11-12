#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        set<string> se;
        for (int i = 0; i < s.size(); i++) {
            for (int j = 1; j <= s.size() - i; j++) {
                string st = s.substr(i,j);
                //cout << st << '\n';
                se.insert(st);
            }
        }
        cout << se.size() << '\n';
    }

    return 0;
}

