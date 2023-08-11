#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    vector<int> vs;
    int curr = 0;
    char c = '#';
    int i = 0;
    while (i < s.size() && s[i] == 'o') i++;
    int lcnt = 0, rcnt = 0;
    for (; i < s.size(); i++) {
        if (s[i] != c) {
            if (c == 'v') rcnt += curr-1;
            if (c != '#') vs.push_back(curr);
            curr = 1;
            c = s[i];
        }
        else {
            curr++;
        }
    }
    if (c == 'v') {
        vs.push_back(curr);
        rcnt += curr-1;
    }
    ll ans = 0;
    for (int i = 0; i < vs.size(); i++) {
        if (i % 2 == 0) {
            rcnt -= vs[i] - 1;
            lcnt += vs[i] - 1;
        }
        else {
            ans += 1LL*vs[i]*lcnt*rcnt;
        }
    }
    cout << ans << '\n';
}

