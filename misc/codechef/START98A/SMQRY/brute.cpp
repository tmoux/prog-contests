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



struct DSU {

  int n;

  vector<int> par;

  vector<int> diam;

  DSU(int _n) {

    n = _n;

    par.resize(n+1, -1);

    diam.resize(n+1, 0);

  }



  int Find(int i) {

    return par[i] < 0 ? i : par[i] = Find(par[i]);

  }



  bool Union(int x, int y) { // return true if x and y were not connected

    x = Find(x);

    y = Find(y);

    if (x == y) return false;

    if (par[x] > par[y]) swap(x, y);

    par[x] += par[y];

    par[y] = x;

    ckmax(diam[x], diam[y]);

    return true;

  }

};



void solve() {

  int N, Q; cin >> N >> Q;

  vector<int> furthest(N+1);

  DSU dsu(N);



  vector<vector<int>> adj(N+1);

  int score = 0;

  int sumDiam = 0;



  vector<bool> vis(N+1);

  REP(Q) {

    int u, v; cin >> u >> v;

    // int x = score ^ u;

    // int y = score ^ v;
    int x = u, y = v;

    assert(dsu.Find(x) != dsu.Find(y));



    int dx = furthest[x], dy = furthest[y];

    int tr = dx + 1 + dy;

    queue<pair<int, int>> q;

    vector<int> toClear;

    auto BFS = [&]() {

      while (!q.empty()) {

        auto [d, i] = q.front(); q.pop();

        vis[i] = 1;

        toClear.push_back(i);

        ckmax(furthest[i], d);

        for (int j: adj[i]) {

          if (!vis[j]) {

            q.push({1 + d, j});

          }

        }

      }

    };

    q.push({1 + dx, y}); BFS();

    q.push({1 + dy, x}); BFS();



    for (auto i: toClear) vis[i] = 0;



    adj[x].push_back(y);

    adj[y].push_back(x);

    sumDiam -= dsu.diam[dsu.Find(x)];

    sumDiam -= dsu.diam[dsu.Find(y)];

    dsu.Union(x, y);

    x = dsu.Find(x);

    ckmax(dsu.diam[x], tr);

    sumDiam += dsu.diam[x];



    score ^= sumDiam;

  }

  cout << score << '\n';

}



int main() {

  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int T; cin >> T;

  while (T--) solve();

}
