#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int q = 1; q <= t; q++) {
        cout << "Case #" << q << ": ";
        int n; cin >> n;
        vector<pair<pair<int,int>,int>> v;
        for (int i = 0; i < n; i++) {
            int a, b; cin >> a >> b;
            v.push_back({{a,b},i});
        }
        sort(v.begin(),v.end());
        int C = -1, J = -1;
        vector<char> ans(n);
        bool poss = true;
        for (auto pp: v) {
            int id = pp.second;
            auto p = pp.first;
            if (C <= p.first) {
                C = p.second;
                ans[id] = 'C';
            }
            else if (J <= p.first) {
                J = p.second;
                ans[id] = 'J';
            }
            else {
                poss = false;
                break;
            }
        }
        if (!poss) {
            cout << "IMPOSSIBLE\n";
        }
        else {
            for (int i = 0; i < n; i++) {
                cout << ans[i];
            }
            cout << '\n';
        }
    }
}

