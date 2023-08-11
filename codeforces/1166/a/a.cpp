#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    map<char,int> mp;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        mp[s[0]]++;
    }
    int ans = 0;
    for (auto p: mp) {
        int x = p.second/2, y = p.second-x;
        ans += x*(x-1)/2;
        ans += y*(y-1)/2;
    }
    cout << ans << endl;
}

