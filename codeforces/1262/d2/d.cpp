#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m, a[maxn];
const ll INF = 1e18;

template <class K, class V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<K, V, std::less<K>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

int ans[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    vector<pair<int,int>> v;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        v.push_back({a[i],i});
    }

    vector<pair<pair<int,int>,int>> queries;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int k, pos; cin >> k >> pos;
        queries.push_back({{k,pos},i});
    }
    sort(queries.begin(),queries.end(),[](auto a, auto b) {
            return a.first.first < b.first.first;
            });
    sort(v.begin(),v.end(),[](auto a, auto b) {
            return a.first != b.first ? a.first > b.first : a.second < b.second;});

    int pt = 0;
    ordered_set<int> os;
    for (auto p: queries) {
        int k = p.first.first;
        int pos = p.first.second;
        int id = p.second;
        while (pt < k) {
            os.insert(v[pt].second);                                  pt++; 
        }
        int i = *os.find_by_order(pos-1);
        ans[id] = a[i];
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << '\n';
    }
}
