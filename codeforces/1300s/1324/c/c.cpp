#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        vector<int> v;
        string s; cin >> s;
        v.push_back(0);
        for (int i = 1; i <= s.size(); i++) {
            if (s[i-1] == 'R') v.push_back(i);
        }
        v.push_back(s.size()+1);
        int ans = 0;
        for (int i = 1; i < v.size(); i++) {
            ans = max(ans,v[i]-v[i-1]);
        }
        cout << ans << endl;
    }
}
