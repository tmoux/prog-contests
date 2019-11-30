#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n, a[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<pair<int,int>> v;
    for (int i = 1; i <= n;i ++) {
        cin >> a[i];
        v.push_back({a[i],i});
    }
    ll min_sum = 0;
    sort(v.begin(),v.end());
    set<int> seen;
    seen.insert(0); seen.insert(n+1);
    for (auto p: v) {
        auto l = seen.lower_bound(p.second);
        assert(l != seen.begin());
        ll x = p.second-*prev(l);
        ll y = *l-p.second;
        min_sum += 1LL*p.first*x*y;
        seen.insert(p.second);
    }
    ll max_sum = 0;
    sort(v.begin(),v.end(),[](auto a, auto b) {
            return a.first != b.first ? a.first > b.first : a.second < b.second;
            });
    seen.clear();
    seen.insert(0); seen.insert(n+1);
    for (auto p: v) {
        auto l = seen.lower_bound(p.second);
        assert(l != seen.begin());
        ll x = p.second-*prev(l);
        ll y = *l-p.second;
        max_sum += 1LL*p.first*x*y;
        seen.insert(p.second);
    }
    cout << (max_sum - min_sum) << '\n';
}
