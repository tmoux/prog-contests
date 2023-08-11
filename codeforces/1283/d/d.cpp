#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m;

set<int> s;
int dist(int x) {
    auto it = s.lower_bound(x);
    if (it == s.end()) return x-*prev(it);
    if (it == s.begin()) return *it-x;
    return min(x-*prev(it),*it-x);
}

set<int> u;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int xi;
        cin >> xi;
        s.insert(xi);
        u.insert(xi);
    }
    set<pair<int,int>> q;
    for (int x: s) {
        if (!u.count(x+1)) {
            q.insert({dist(x+1),x+1});
            u.insert(x+1);
        }
        if (!u.count(x-1)) {
            q.insert({dist(x-1),x-1});
            u.insert(x-1);
        }
    }
    ll ans = 0;
    vector<int> ret;
    while (m > 0) {
        auto p = *q.begin();
        q.erase(q.begin());
        ans += p.first;
        ret.push_back(p.second);
        m--;
        int x = p.second;

        if (!u.count(x+1)) {
            q.insert({dist(x+1),x+1});
            u.insert(x+1);
        }
        if (!u.count(x-1)) {
            q.insert({dist(x-1),x-1});
            u.insert(x-1);
        }
    }
    cout << ans << '\n';
    for (auto i: ret) {
        cout << i << ' ';
    }
    cout << '\n';
}

