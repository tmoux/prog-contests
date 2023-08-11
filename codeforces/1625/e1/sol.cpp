#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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
  void reset(int i) {
    ll x = sum(i) - sum(i-1);
    add(i, -x);
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
  vector<vector<int>> adj(n);
  vector<int> index(n, -1), childIndex(n, -1);
  vector<int> end(n, -1);
  int idx = 1;
  for (int i = 0; i < n; i++) {
    if (ignore[i]) continue;
    if (s[i] == '(') {
      int id = idx++;
      index[i] = id;
      if (!opens.empty()) {
        int p = opens.top();
        childIndex[id] = adj[p].size();
        adj[p].push_back(id);
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
    return 1LL*x*(x-1)/2;
  };

  int N = idx-1;

  Fenwick fen(N); 
  for (int i = 1; i <= N; i++) {
    fen.add(i, 1 + choose2(adj[i].size()));
  }

  while (q--) {
    int t, l, r; cin >> t >> l >> r;
    l = index[l];
    r = index[r];

    if (t == 1) {
      assert(false);
    }
    else if (t == 2) {
      ll ans = fen.sum(end[r]) - fen.sum(l-1);
      ans += choose2(childIndex[r]-childIndex[l]+1);
      cout << ans << '\n';
    }
    else assert(false);
  }
}
