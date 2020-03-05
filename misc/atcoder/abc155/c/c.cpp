#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    map<string,int> mp;
    for (int i = 0; i < n; i++) {
        string si; cin >> si;
        mp[si]++;
    }
    map<int,vector<string>> v;
    for (auto p: mp) {
        v[p.second].push_back(p.first);
    }
    vector<string> u = v.rbegin()->second;
    sort(u.begin(),u.end());
    for (auto s: u) {
        cout << s << '\n';
    }
}

