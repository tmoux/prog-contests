#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

// Template {{{
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

namespace std {
  template<class Fun>
  class y_combinator_result {
    Fun fun_;
  public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
   
    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
      return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
  };
   
  template<class Fun>
  decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
  }
} // namespace std

template<typename T>
concept Container = requires(T a)
{
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
};

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v) 
  requires Container<U<T>> && (!requires(std::ostream o, T a) { operator<<(o, a); })
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}
// }}}

void solve() {
  int n, m; cin >> n >> m;
  vector<set<pair<int,int>>> ones(n), twos(n);
  set<tuple<int,int,int>> direction;
  vector<pair<int,int>> edges;
  vector<int> weights;
  vector<int> sum(n);
  F0R(id, m) {
    int u, v, w; cin >> u >> v >> w;
    u--; v--;
    edges.push_back({u, v});
    weights.push_back(w);
    sum[u] += w;
    sum[v] += w;
    if (w == 1) {
      ones[u].insert({v, id});
      ones[v].insert({u, id});
    }
    else {
      twos[u].insert({v, id});
      twos[v].insert({u, id});
    }
  }

  struct Shed {
    int a, b, c, id1, id2, id3;
  };

  vector<Shed> sheds;
  auto shed_edge = [&](int a, int b, int c, int id1, int id2, int id3, vector<set<pair<int,int>>>& adj) -> void {
    adj[a].erase({b, id1});
    adj[b].erase({a, id1});

    adj[a].erase({c, id2});
    adj[c].erase({a, id2});

    adj[b].insert({c, id3});
    adj[c].insert({b, id3});

    sheds.push_back({a, b, c, id1, id2, id3});
  };

  int new_id_counter = m;

  F0R(i, n) {
    while (sz(ones[i]) >= 2) {
      auto [b, id1] = *ones[i].begin();
      auto [c, id2] = *next(ones[i].begin());

      shed_edge(i, b, c, id1, id2, new_id_counter++, ones);
    }

    while (sz(twos[i]) >= 2) {
      auto [b, id1] = *twos[i].begin();
      auto [c, id2] = *next(twos[i].begin());

      shed_edge(i, b, c, id1, id2, new_id_counter++, twos);
    }
  }

  auto fixEdges = [&]() -> void {
    vector<bool> visited(n, false);
    auto dfs = y_combinator([&](auto dfs, int i) -> void {
      assert(sz(ones[i]) <= 1 && sz(twos[i]) <= 1);
      visited[i] = true;
      for (auto adj : {&ones, &twos}) {
        if (!(*adj)[i].empty() && !visited[(*adj)[i].begin()->first]) {
          auto [j, id] = *(*adj)[i].begin();
          direction.insert({i, j, id});
          dfs(j);
        }
      }
    });
    auto dfs_cycle = y_combinator([&](auto dfs_cycle, int i, bool b) -> void {
      assert(sz(ones[i]) == 1 && sz(twos[i]) == 1);
      if (!visited[i]) {
        visited[i] = true;
        auto [j, id] = b ? *ones[i].begin() : *twos[i].begin();
        direction.insert({i, j, id});
        dfs_cycle(j, !b);
      }
    });
    // fill in paths
    F0R(i, n) {
      if (!visited[i] && sz(ones[i]) + sz(twos[i]) == 1) dfs(i);
    }
    // fill in cycles
    F0R(i, n) {
      if (!visited[i] && sz(ones[i]) + sz(twos[i]) == 2) {
        dfs_cycle(i, true);
      }
    }
  };
  fixEdges();

  auto unshed_edge = [&](int a, int b, int c, int id1, int id2, int id3) -> void {
    if (b == c) {
      direction.insert({a, b, id1});
      direction.insert({c, a, id2});
    }
    else {
      assert(direction.count({b, c, id3}) ^ direction.count({c, b, id3}));
      if (direction.count({b, c, id3})) {
        direction.insert({b, a, id1});
        direction.insert({a, c, id2});
      }
      else {
        direction.insert({a, b, id1});
        direction.insert({c, a, id2});
      }
    }
  };

  for (auto it = sheds.rbegin(); it != sheds.rend(); ++it) {
    auto [a, b, c, id1, id2, id3] = *it;
    unshed_edge(a, b, c, id1, id2, id3);
  }

  // output answer
  vector<int> ans(m);
  for (auto [a, b, id]: direction) {
    if (id < m) {
      if (edges[id] == make_pair(a, b)) {
        ans[id] = 1;
      }
      else ans[id] = 2;
    }
  }
  int max_beauty = count_if(all(sum), [](int i){return i % 2 == 1;});
  cout << max_beauty << '\n';
  for (auto i: ans) cout << i;
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  //int T; cin >> T;
  int T = 1;
  while (T--) solve();
}
