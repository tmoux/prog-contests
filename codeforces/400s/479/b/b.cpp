#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, k;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    set<pair<int,int>> s;
    for (int i = 1; i <= n; i++) {
        int ai; cin >> ai;
        s.insert({ai,i});
    }
    int cnt = 0;
    vector<pair<int,int>> ans;
    for (int i = 0; i < k; i++) {
        auto p1 = *s.rbegin(), p2 = *s.begin();
        if (p1.first <= p2.first+1) break;
        ans.push_back({p1.second,p2.second});
        s.erase(p1); s.erase(p2);
        s.insert({p1.first-1,p1.second});
        s.insert({p2.first+1,p2.second});
    }
    cout << (s.rbegin()->first-s.begin()->first) << ' ';
    cout << ans.size() << '\n';
    for (auto p: ans) {
        cout << p.first << ' ' << p.second << '\n';
    }
}

