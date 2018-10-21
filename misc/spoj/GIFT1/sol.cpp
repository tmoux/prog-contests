#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int np; cin >> np;
    map<string,int> mp;
    vector<string> ans;
    for (int i = 0; i < np; i++) {
        string s; cin >> s;
        ans.push_back(s);
        mp[s] = 0;
    }
    string s;
    while (cin >> s) {
        int t, v; cin >> t >> v;
        if (v == 0) continue;
        mp[s] -= t;
        mp[s] += t%v;
        //cout << t << ' ' << v << ": " << t/v << '\n';
        for (int a = 0; a < v; a++) {
            string ss; cin >> ss;
            mp[ss] += t/v;
        }
    }
    for (string s: ans) {
        cout << s << ' ' << mp[s] << '\n';
    }

    return 0;
}

