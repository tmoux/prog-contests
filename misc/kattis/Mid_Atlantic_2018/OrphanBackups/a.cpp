#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    set<string> indexes;
    string s;
    while (true) {
        getline(cin,s);
        //cout << s << '\n';
        if (s.empty()) break;
        indexes.insert(s);
    }
    map<string,vector<string>> backups;
    set<string> bb;
    while (getline(cin,s)) {
        int i = s.find_last_of('_');
        string r = s.substr(0,i);
        i = r.find_last_of('_');
        r = r.substr(0,i);
        //cout << r << '\n';
        backups[r].push_back(s);
        bb.insert(r);
    }
    assert(!indexes.empty() && !backups.empty() && !bb.empty());
    vector<string> a1, a2;
    for (auto& p: backups) {
        if (!indexes.count(p.first)) {
            for (string s: p.second) {
                a1.push_back("F " + s);
            }
        }
    }
    for (string s: indexes) {
        if (!bb.count(s)) {
            a2.push_back("I " + s);
        }
    }
    if (a1.empty() && a2.empty()) {
        cout << "No mismatches.\n";
    }
    else {
        sort(a1.begin(),a1.end());
        sort(a2.begin(),a2.end());
        for (auto s: a1) {
            cout << s << '\n';
        }
        for (auto s: a2) {
            cout << s << '\n';
        }
    }
}

