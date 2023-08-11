#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using ll = long long;

template <class K, class V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<K, V, std::less<K>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

struct Fenwick // {{{
{
  int n;
  vector<ll> bit;
  Fenwick() {}
  Fenwick(int n_) {
    n = n_;
    bit.resize(n+1,0);
  }
  void add(int i, ll x) {
    for (; i <= n; i += i & (-i))
      bit[i] += x;
  }

  ll sum(int i) {
    ll r = 0;
    for (; i; i -= i & (-i)) {
      r += bit[i];
    }
    return r;
  }
}; // }}}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, q; cin >> n >> q;
  string s; cin >> s;
  s = '(' + s + ')';
  // build tree {{{
  vector<bool> ignore(s.size(), false);
  stack<int> opens;
  for (int i = 1; i <= n; i++) {
    if (s[i] == '(') {
      opens.push(i);
    }
    else {
      if (!opens.empty()) {
        opens.pop();
      }
      else ignore[i] = true;
    }
  }
  while (!opens.empty()) {
    ignore[opens.top()] = true;
    opens.pop();
  }
  n += 2; // n too small causes crazy UB
  vector<int> par(n);
  vector<ordered_set<int>> adj(n);
  vector<int> index(n, -1);
  vector<int> end(n, -1);
  int idx = 1;
  for (int i = 0; i < n; i++) {
    if (ignore[i]) continue;
    if (s[i] == '(') {
      int id = idx++;
      index[i] = id;
      if (!opens.empty()) {
        int p = opens.top();
        par[id] = p;
        adj[p].insert(id);
      }
      opens.push(id);
    }
    else {
      assert(!opens.empty());
      index[i] = opens.top();
      end[opens.top()] = idx-1;
      opens.pop();
    }
  } // }}}
  auto choose2 = [](ll x) -> ll {
    return x*(x-1)/2;
  };

  int N = idx-1;
  Fenwick fen(N); 
  for (int i = 1; i <= N; i++) 
    fen.add(i, 1 + choose2(adj[i].size()));

  while (q--) {
    int t, l, r; cin >> t >> l >> r;
    l = index[l];
    r = index[r];

    if (t == 1) {
      assert(l == r);
      assert(adj[l].empty());
      fen.add(l, -1);
      adj[par[l]].erase(l);
      fen.add(par[l], -adj[par[l]].size());
    }
    else if (t == 2) {
      assert(par[l] == par[r]);
      int p = par[l];
      ll ans = fen.sum(end[r]) - fen.sum(l-1);
      ans += choose2(adj[p].order_of_key(r)-adj[p].order_of_key(l)+1);
      cout << ans << '\n';
    }
    else assert(false);
  }
}
