#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> z_function(string s) {
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

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s, t; cin >> s >> t;
    map<char,int> mp;
    for (char c: s) mp[c]++;
    auto z = z_function(t);
    int pos = t.size();
    int len = 0;
    for (int i = 0; i < t.size(); i++) {
        if (z[i] == t.size() - i) {
            pos = i;
            len = z[i];
            break;
        }
    }
    string ret = "";
    if (pos != t.size()) {
        map<char,int> cnt;
        for (char c: t) {
            cnt[c]++;
        }
        if (mp['0'] >= cnt['0'] && mp['1'] >= cnt['1']) {
            mp['0'] -= cnt['0'];
            mp['1'] -= cnt['1'];
            ret += t;
        }
        else {
            cout << s << '\n';
            return 0;
        }
    }
    map<char,int> cnt;
    string sub = t.substr(len);
    for (char c: sub) {
        cnt[c]++;
    }
    while (mp['0'] >= cnt['0'] && mp['1'] >= cnt['1']) {
        mp['0'] -= cnt['0'];
        mp['1'] -= cnt['1'];
        ret += sub;
    }
    while (mp['0'] > 0) {
        mp['0']--;
        ret += '0';
    }
    while (mp['1'] > 0) {
        mp['1']--;
        ret += '1';
    }
    cout << ret << '\n';
}

