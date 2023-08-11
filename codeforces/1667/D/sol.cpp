#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

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

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  os << '[';
  string sep;
  for (const T &x : v) os << sep << x, sep = ", ";
  return os << ']';
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

void solve() {
  int N; cin >> N;
  vector<set<int>> adj(N);
  F0R(i, N-1) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a].insert(b);
    adj[b].insert(a);
  }

  vector<set<int>> valid(2);
  vector<vector<set<int>>> leafs(2, vector<set<int>>(N));

  auto isLeaf = [&](int i) {
    return sz(adj[i]) == 1;
  };

  auto updateVertex = [&](int i) {
    if (isLeaf(i)) {
      int j = *adj[i].begin();
      leafs[0][j].insert(i);

      if (sz(adj[j]) % 2 == 1) valid[0].insert(j);

      if (sz(adj[j]) == 2) {
        int l = *adj[j].begin(), k = *next(adj[j].begin());
        if (!isLeaf(l)) swap(l, k);
        if (isLeaf(l)) {
          leafs[1][k].insert(j);
          if (sz(adj[k]) % 2 == 0) valid[1].insert(k);
        }
      }
    }
    else if (sz(adj[i]) == 2) {
      int j = *adj[i].begin(), k = *next(adj[i].begin());
      if (!isLeaf(j)) swap(j, k);
      if (isLeaf(j)) {
        leafs[1][k].insert(i);
        if (sz(adj[k]) % 2 == 0) valid[1].insert(k);
      }
    }

    if (sz(adj[i]) % 2 == 1 && !leafs[0][i].empty()) valid[0].insert(i);
    if (sz(adj[i]) % 2 == 0 && !leafs[1][i].empty()) valid[1].insert(i);
  };

  set<pair<int, int>> S;
  vector<pair<int, int>> ans;
  auto removeEdge = [&](int i, int j) -> void {
    if (S.count({i, j})) return;
    // cout << "removing edge " << i+1 << ' ' << j+1 << endl;
    S.insert({i, j});
    S.insert({j, i});
    ans.push_back({i, j});
    adj[i].erase(j);
    adj[j].erase(i);


    F0R(k, 2) {
      if (valid[k].count(i)) valid[k].erase(i);
      if (leafs[k][i].count(j)) leafs[k][i].erase(j);
    }
    F0R(k, 2) {
      if (valid[k].count(j)) valid[k].erase(j);
      if (leafs[k][j].count(i)) leafs[k][j].erase(i);
    }

    updateVertex(i);
    updateVertex(j);
  };

  F0R(i, N) {
    updateVertex(i);
  }


  while (true) {
    bool p = false;
    // for (auto x: valid[0]) {
    //   cout << x+1 << ' ';
    // }
    // cout << endl;
    // for (auto x: valid[1]) {
    //   cout << x+1 << ' ';
    // }
    // cout << endl;
    F0R(k, 2) {
      if (!valid[k].empty()) {
        int i = *valid[k].begin();
        // cout << "processing " << i << ' ' << k << endl;
        assert(!leafs[k][i].empty());
        int j = *leafs[k][i].begin();
        leafs[k][i].erase(j);

        removeEdge(i, j);

        p = true;
        break;
      }
    }

    if (!p) break;
  }

  if (sz(ans) == N-1) {
    cout << "YES\n";
    for (auto [a, b]: ans) {
      cout << a+1 << ' ' << b+1 << '\n';
    }
  }
  else {
    cout << "NO\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
