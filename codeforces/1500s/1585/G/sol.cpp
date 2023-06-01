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

const int maxn = 5e5+5;
int N;
vector<int> adj[maxn];

struct Bag {
  vector<int> v;
  multiset<int> s;

  void update(int i, int x) {
    auto it = s.find(v[i]);
    assert(it != s.end());
    s.erase(it);
    v[i] ^= x;
    s.insert(v[i]);
  }

  void insert(int x) {
    v.push_back(x);
    s.insert(x);
  }

  int mex(int x) {
    while (s.count(x)) x++;
    return x;
  }
};
using T = Bag;

void merge(T& a, T& b) {
  F0R(i, sz(a.v)) {
    a.update(sz(a.v)-1-i, b.v[sz(b.v)-1-i]);
  }
  b.v.clear(); b.s.clear();
}

int mex(vector<int> v) {
  sort(all(v)); v.erase(unique(all(v)), v.end());
  F0R(i, sz(v)) if (v[i] != i) return i;
  return sz(v);
}


int depth[maxn];
void prep(int i) {
  depth[i] = adj[i].empty() ? 1 : 1e9;
  for (int j: adj[i]) {
    prep(j);
    ckmin(depth[i], depth[j]+1);
  }
}

T* dfs(int i) {
  T* v = new T;
  v->insert(0);
  sort(all(adj[i]), [&](auto a, auto b) { return depth[a] < depth[b]; });
  F0R(idx, sz(adj[i])) {
    int j = adj[i][idx];
    auto vj = dfs(j);
    if (idx == 0) v = vj;
    else merge(*v, *vj);
  }

  if (sz(adj[i]) == 1) {
    v->insert(v->mex(v->v.back()));
  }
  else {
    v->insert(mex(v->v));
  }

  return v;
}

void solve() {
  cin >> N;
  FOR(i, 0, N+1) adj[i].clear();
  FOR(i, 1, N+1) {
    int p; cin >> p;
    adj[p].push_back(i);
  }
  prep(0);
  int ans = 0;
  for (int i: adj[0]) {
    auto v = dfs(i);
    ans ^= v->v.back();
  }
  cout << (ans ? "YES" : "NO") << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
