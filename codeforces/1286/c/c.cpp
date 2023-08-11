#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int n;

int ch(int x) {
    return x*(x-1)/2 + x;
}

map<char,int> getCnt(string s) {
    map<char,int> ret;
    for (char c: s) ret[c]++;
    return ret;
}

char getDiff(map<char,int> a, map<char,int> b) {
    for (auto p: a) {
        if (b[p.first] != p.second) return p.first;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    cout << "? 1 " << n << endl;
    map<int,multiset<string>> mp;
    for (int i = 0; i < ch(n); i++) {
        string s; cin >> s;
        sort(s.begin(),s.end());
        mp[s.size()].insert(s);
    }

    if (n == 1) {
        cout << "! " << *mp[1].begin() << '\n';
        return 0;
    }

    cout << "? 2 " << n << endl;
    map<int,multiset<string>> mp2;
    for (int i = 0; i < ch(n-1); i++) {
        string s; cin >> s;
        sort(s.begin(),s.end());
        mp2[s.size()].insert(s);
    }

    for (int i = 1; i <= n-1; i++) {
        for (string s: mp2[i]) {
            auto it = mp[i].find(s);
            if (it != mp[i].end()) mp[i].erase(it);
        }
    }

    map<char,int> cur;
    string s;
    for (int i = 1; i <= n; i++) {
        char c = getDiff(getCnt(*mp[i].begin()),cur);
        s += c;
        cur[c]++;
    }
    cout << "! " << s << endl;
    return 0;
}

