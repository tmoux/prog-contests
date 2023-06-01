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

const int maxn = 2e5+5;
int ans[maxn];

using P = pair<int, int>;
map<pair<int, int>, set<int>*> mp;
void touch(P b) {
  if (!mp.count(b)) mp[b] = new set<int>;
}

void mergeSet(set<int>& a, set<int>& b, int id) {
  if (sz(a) < sz(b)) swap(a, b);
  for (auto i: b) {
    if (a.count(i)) {
      a.erase(i);
      ans[i] = id;
    }
    else a.insert(i);
  }
}

struct T {
  set<P> s;

  void insert(P x, int id) {
    auto it = s.lower_bound(x);
    touch(x);
    set<int>* xs = mp[x];
    if (it != s.begin() && prev(it)->second + 1 == x.first) {
      x.first = prev(it)->first;
      if (mp.count(*prev(it))) mergeSet(*xs, *mp[*prev(it)], id);
      s.erase(prev(it));
    }
    it = s.upper_bound(x);
    if (it != s.end() && it->first - 1 == x.second) {
      x.second = it->second;
      if (mp.count(*it)) mergeSet(*xs, *mp[*it], id);
      s.erase(it);
    }

    mp[x] = xs;
    s.insert(x);
  }
};

void merge(T& a, T& b, int id) {
  if (sz(a.s) < sz(b.s)) swap(a, b);
  for (auto x: b.s) {
    a.insert(x, id);
  }
}

struct DSU {
  int n;
  vector<int> par;
  vector<T*> bag;

  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
    bag.resize(n+1);
    F0R(i, n+1) {
      bag[i] = new T;
      bag[i]->insert({i, i}, 0);
    }
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y, int id) { // return true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    merge(*bag[x], *bag[y], id);

    // cout << "merging " << x << ' ' << y << endl;
    // for (auto p: bag[x]->s) {
    //   cout << p << ": " << *mp[p] << endl;
    // }
    return true;
  }

  ~DSU() {
    F0R(i, n+1) delete bag[i];
  }
};

void solve() {
  mp.clear();
  int N, M, Q; cin >> N >> M >> Q;
  vector<pair<int, int>> edges(M);
  F0R(i, M) {
    int a, b; cin >> a >> b;
    edges[i] = {a, b};
  }
  vector<pair<int, int>> queries(Q);
  fill(ans, ans+Q, 0);

  DSU dsu(N);
  F0R(i, Q) {
    int a, b; cin >> a >> b;
    queries[i] = {a, b};
    if (a != b) {
      touch({a, a});
      touch({b, b});
      mp[{a, a}]->insert(i);
      mp[{b, b}]->insert(i);
    }
  }

  F0R(i, M) {
    auto [a, b] = edges[i];
    dsu.Union(a, b, i+1);
  }

  F0R(i, Q) {
    cout << ans[i] << " \n"[i == Q-1];
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
