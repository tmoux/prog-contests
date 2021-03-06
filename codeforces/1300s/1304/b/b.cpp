#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    set<string> s;
    for (int i = 0; i < n; i++) {
        string ss; cin >> ss;
        s.insert(ss);
    }
    vector<string> ans;
    string mid = "";
    for (string t: s) {
        string rev = t;
        reverse(rev.begin(),rev.end());
        if (t < rev && s.count(rev)) {
            ans.push_back(t);
        }
        else if (t == rev) {
            mid = t;
        }
    }
    string ret = "";
    for (int i = 0; i < ans.size(); i++) {
        ret += ans[i];
    }
    if (mid.size() > 0) ret += mid;
    for (int i = (int)ans.size()-1; i >= 0; i--) {
        string rev = ans[i];
        reverse(rev.begin(),rev.end());
        ret += rev;
    }
    cout << ret.size() << endl;
    cout << ret << endl;
}
