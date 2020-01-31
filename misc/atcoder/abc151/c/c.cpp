#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    map<int,int> mp;
    set<int> ac;
    int ans = 0, pen = 0;
    for (int i = 0; i < m; i++) {
        int p; string s; cin >> p >> s;
        if (ac.count(p)) {
            continue;
        }
        else {
            if (s == "WA") {
                mp[p]++;
            }
            else {
                ans++;
                pen += mp[p];
                ac.insert(p);
            }
        }
    }
    cout << ans << ' ' << pen << '\n';
}

