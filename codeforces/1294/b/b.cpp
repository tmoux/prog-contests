#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<pair<int,int>> v;
        for (int i = 0; i < n; i++) {
            int x, y; cin >> x >> y;
            v.push_back({x,y});
        }
        sort(v.begin(),v.end());
        bool poss = true;
        for (int i = 1; i < n; i++) {
            if (v[i].second < v[i-1].second) {
                poss = false;
                break;
            }
        }
        if (!poss) {
            cout << "NO\n";
        }
        else {
            int x = 0, y = 0;
            string ret = "";
            for (auto p: v) {
                while (x < p.first) {
                    x++;
                    ret += 'R';
                }
                while (y < p.second) {
                    y++;
                    ret += 'U';
                }
            }
            cout << "YES\n";
            cout << ret << '\n';
        }
    }
}

