#include <bits/stdc++.h>
using namespace std;
using ll = long long;

set<char> vowels = {'a','e','i','o','u'};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s, t; cin >> s >> t;
    if (s.size() != t.size()) {
        cout << "No" << '\n';
    }
    else {
        bool poss = true;
        for (int i = 0; i < s.size(); i++) {
            bool t1 = vowels.count(s[i]);
            bool t2 = vowels.count(t[i]);
            if (t1 ^ t2) {
                poss = false;
                break;
            }
        }
        cout << (poss ? "Yes" : "No") << '\n';
    }

    return 0;
}

