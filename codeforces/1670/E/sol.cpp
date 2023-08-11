#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define F0R(i, a) for (int i = 0; i < (a); i++)

namespace std {
template <class Fun>
class y_combinator_result {
  Fun fun_;

  public:
  template <class T>
  explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

  template <class... Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}  // namespace std

void solve() {
  int P; cin >> P;
  int N = 1 << P;
  vector<vector<int>> adj(N);
  map<pair<int, int>, int> mp;
  F0R(i, N-1) {
    int x, y; cin >> x >> y;
    x--, y--;
    mp[{x, y}] = mp[{y, x}] = i;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  vector<int> ans(N), edge_ans(N-1);
  auto dfs = y_combinator([&](auto dfs, int i, int p, int d, int& t) -> void {
    ans[i] = t + (d ? 0 : 1<<P);
    for (int j: adj[i]) if (j != p) {
      t++;
      edge_ans[mp[{i, j}]] = t + (d ? 0 : 1<<P);
      dfs(j, i, d^1, t);
    }
  });

  int t = 0;
  dfs(0, 0, 0, t);

  cout << 1 << '\n';
  F0R(i, N) cout << ans[i] << " \n"[i == N-1];
  F0R(i, N-1) cout << edge_ans[i] << " \n"[i == N-2];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
