#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string s;
vector<bool> bad;

vector<int> f(int l, int r) {
    string curr;
    vector<int> ret;
    for (int i = l; i <= r; i++) {
        if (bad[i]) continue;
        curr += s[i];
        if (curr.size() >= 5 && curr.substr(curr.size()-5) == "twone") {
            bad[i-2] = true;
            ret.push_back(i-2);
        }
    }
    curr.clear();
    int prev = -1;
    for (int i = l; i <= r; i++) {
        if (bad[i]) continue;
        curr += s[i];
        if (curr.size() >= 3 && (curr.substr(curr.size()-3) == "one" || curr.substr(curr.size()-3) == "two")) {
            bad[prev] = true;
            ret.push_back(prev);
            curr.pop_back();
            curr.pop_back();
            curr += s[i];
        }
        prev = i;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> s;
        s += '#';
        bad = vector<bool>(s.size(),false);
        vector<int> ans;
        int l = -1;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != 't' && s[i] != 'w' && s[i] != 'o' && s[i] != 'n' && s[i] != 'e') {
                if (l != -1) {
                    auto v = f(l,i-1);
                    for (int j: v) {
                        ans.push_back(j);
                    }
                    l = -1;
                }
            }
            else {
                if (l == -1) l = i;
            }
        }
        cout << ans.size() << '\n';
        for (auto j: ans) {
            cout << j+1 << ' ';
        }
        cout << '\n';
    }
}

