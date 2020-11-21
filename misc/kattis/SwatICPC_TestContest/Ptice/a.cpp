#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int cnt(string a, string b) {
    int ans = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i]) ans++;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string s; cin >> s;
    string adrian = "", bruno = "", goran = "";
    for (int i = 0; i < n; i++) {
        adrian += "ABC";
        bruno += "BABC";
        goran += "CCAABB";
    }
    int best = -1;
    vector<string> ret = {};
    if (cnt(s,adrian) > best) {
        best = cnt(s,adrian);
        ret = {"Adrian"};
    }
    else if (cnt(s,adrian) == best) {
        ret.push_back("Adrian");
    }
    if (cnt(s,bruno) > best) {
        best = cnt(s,bruno);
        ret = {"Bruno"};
    }
    else if (cnt(s,bruno) == best) {
        ret.push_back("Bruno");
    }
    if (cnt(s,goran) > best) {
        best = cnt(s,goran);
        ret = {"Goran"};
    }
    else if (cnt(s,goran) == best) {
        ret.push_back("Goran");
    }
    sort(ret.begin(),ret.end());
    cout << best << '\n';
    for (auto s: ret) {
        cout << s << '\n';
    }
}

