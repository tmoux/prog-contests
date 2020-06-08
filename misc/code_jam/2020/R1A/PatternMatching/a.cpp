#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string get_prefix(string s) {
    string ret = "";
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '*') break;
        ret += s[i];
    }
    return ret;
}

string get_suffix(string s) {
    int i = s.size()-1;
    while (s[i] >= 0 && s[i] != '*') i--;
    return s.substr(i+1);
}

string get_middle(string s) {
    string ret = "";
    int l = 0;
    while (s[l] != '*') l++;
    int r = s.size()-1;
    while (s[r] != '*') r--;
    for (int i = l; i <= r; i++) {
        if (s[i] != '*') ret += s[i];
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int _ = 1; _ <= t; _++) {
        cout << "Case #" << _ << ": ";
        int n; cin >> n;
        vector<string> v(n);
        vector<string> prefixes, suffixes;
        for (int i = 0; i < n; i++) {
            cin >> v[i];
            prefixes.push_back(get_prefix(v[i]));
            suffixes.push_back(get_suffix(v[i]));
        }
        sort(prefixes.begin(),prefixes.end(),[](auto a, auto b) {
                return a.size() > b.size();
                });
        bool poss = true;
        for (int i = 0; i < prefixes[0].size(); i++) {
            char c = prefixes[0][i];
            for (int j = 0; j < prefixes.size(); j++) {
                if (i < prefixes[j].size() && prefixes[j][i] != c) {
                    poss = false;
                    break;
                }
            }
        }
        sort(suffixes.begin(),suffixes.end(),[](auto a, auto b) {
                return a.size() > b.size();
                });
        for (int i = 0; i < suffixes[0].size(); i++) {
            char c = suffixes[0][suffixes[0].size()-1-i];
            for (int j = 0; j < suffixes.size(); j++) {
                if (((int)suffixes[j].size())-1-i >= 0 && suffixes[j][suffixes[j].size()-1-i] != c) {
                    poss = false;
                    break;
                }
            }
        }
        if (!poss) {
            cout << "*\n";
        }
        else {
            string ret = prefixes[0];
            for (auto s: v) {
                ret += get_middle(s);
            }
            ret += suffixes[0];
            cout << ret << '\n';
        }
    }
}
