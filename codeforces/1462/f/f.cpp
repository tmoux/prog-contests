#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using ll = long long;

template <class K, class V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<K, V, std::less<K>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

const int maxn = 2e5+5;
int n;
void solve() {
  cin >> n;
  vector<pair<int,int>> v(n);
  ordered_set<pair<int,int>> ls, rs;
  for (int i = 0; i < n; i++) {
    int l, r; cin >> l >> r;
    v[i] = {l,r};
    ls.insert({l,i});
    rs.insert({r,i});
  }
  int ans = n;
  for (auto p: v) {
    int l = p.first;
    int r = p.second;

    int tr = rs.order_of_key({l,-1});
    tr += n-ls.order_of_key({r,n});

    //cout << l << ' ' << r << ": " << tr << '\n';
    ans = min(ans,tr);
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) solve();
}
