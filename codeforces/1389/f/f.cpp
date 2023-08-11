#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) begin(x),end(x)

const int maxn = 2e5+5;
int n;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<pair<int,int>> rs;
    vector<pair<int,int>> ons, offs;
    for (int i = 0; i < n; i++) {
        int l, r, t; cin >> l >> r >> t;
        if (t == 1) rs.push_back({r,l});
        else {
            ons.push_back({l,r});
            offs.push_back({r,-1});
        }
    }
    sort(all(ons)); reverse(all(ons));
    sort(all(offs)); reverse(all(offs));
    sort(all(rs));
    multiset<int> s;
    int match = 0;
    for (auto i: rs) {
        while (!ons.empty() && ons.back().first <= i.first) {
            s.insert(ons.back().second);
            ons.pop_back();
        }
        auto it = s.lower_bound(i.second);
        if (it != s.end()) {
            s.erase(it);
            match++;
        }
        //cout << i.first << ' ' << i.second << ": " << match << endl;
    }
    cout << (n-match) << '\n';
}
