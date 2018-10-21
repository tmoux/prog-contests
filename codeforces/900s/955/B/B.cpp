#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    map<char,int> mp;
    for (char c: s) mp[c]++;
    int mx = 0, mn = 1e6;
    for (auto p: mp) {
        mx = max(mx,p.second);
        mn = min(mn,p.second);
    }
    if (mp.size() > 4) {
        cout << "No" << '\n';
        return 0;
    }
    else if (mp.size() == 4) {
        cout << "Yes" << '\n';
    }
    else if (mp.size() == 3) {
        cout << (mx > 1 ? "yes" : "nO") << '\n';
    }
    else if (mp.size() == 2) {
        cout << (mn >= 2 ? "yes" : "nO") << '\n';
    }
    else if (mp.size() == 1) {
        cout << "NO" << '\n';
    }

    return 0;
}

