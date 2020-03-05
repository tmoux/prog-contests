#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    map<char,int> mp;
    for (char c: s) {
        mp[c]++;
    }
    ll ans = 0;
    for (auto p: mp) {
        ans = max(ans,(ll)p.second);
    }
    for (char a = 'a'; a <= 'z'; a++) {
        for (char b = 'a'; b <= 'z'; b++) {
            ll ca = 0;
            ll tr = 0;
            for (int i = 0; i < s.size(); i++) {
                if (s[i] == b) tr += ca;
                if (s[i] == a) ca++;
            }
            ans = max(ans,tr);
        }
    }
    cout << ans << endl;
}

