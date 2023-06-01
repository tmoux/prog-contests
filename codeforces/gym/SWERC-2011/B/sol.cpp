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
  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
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
    return true;
  }

  int sameSet(int x, int y) {
    return Find(x) == Find(y);
  }
};

using vi = vector<int>;
struct ColorMat {
  vi cnt, clr;
  ColorMat(int n, vector<int> clr) : cnt(n), clr(clr) {}
  bool check(int x) { return !cnt[clr[x]]; }
  void add(int x) { cnt[clr[x]]++; }
  void clear() { fill(all(cnt), 0); }
};
struct GraphMat {
  int n;
  DSU uf;
  vector<array<int, 2>> e;
  GraphMat(int _n, vector<array<int, 2>> e) : n(_n), uf(n), e(e) {}
  bool check(int x) { return !uf.sameSet(e[x][0], e[x][1]); }
  void add(int x) { uf.Union(e[x][0], e[x][1]); }
  void clear() { uf = DSU(n); }
};
template <class M1, class M2> struct MatroidIsect {
  int n;
  vector<char> iset;
  M1 m1; M2 m2;
  MatroidIsect(M1 m1, M2 m2, int n) : n(n), iset(n + 1), m1(m1), m2(m2) {}
  vi solve() {
    FOR(i,0,n) if (m1.check(i) && m2.check(i))
      iset[i] = true, m1.add(i), m2.add(i);
    while (augment());
    vi ans;
    FOR(i,0,n) if (iset[i]) ans.push_back(i);
    return ans;
  }
  bool augment() {
    vector<int> frm(n, -1);
    queue<int> q({n}); // starts at dummy node
    auto fwdE = [&](int a) {
      vi ans;
      m1.clear();
      FOR(v, 0, n) if (iset[v] && v != a) m1.add(v);
      FOR(b, 0, n) if (!iset[b] && frm[b] == -1 && m1.check(b))
        ans.push_back(b), frm[b] = a;
      return ans;
    };
    auto backE = [&](int b) {
      m2.clear();
      FOR(cas, 0, 2) FOR(v, 0, n)
        if ((v == b || iset[v]) && (frm[v] == -1) == cas) {
          if (!m2.check(v))
            return cas ? q.push(v), frm[v] = b, v : -1;
          m2.add(v);
        }
      return n;
    };
    while (!q.empty()) {
      int a = q.front(), c; q.pop();
      for (int b : fwdE(a))
        while((c = backE(b)) >= 0) if (c == n) {
            while (b != n) iset[b] ^= 1, b = frm[b];
            return true;
          }
    }
    return false;
  }
};

bool solve() {
  int R; cin >> R;
  if (R == 0) return false;
  vector<int> v;

  vector<array<int, 4>> V(R);
  F0R(i, R) {
    F0R(j, 4) {
      cin >> V[i][j];
      v.push_back(V[i][j]);
    }
  }

  sort(all(v)); v.erase(unique(all(v)), v.end());
  map<int, int> compress;
  int n = 0;
  for (auto i: v) compress[i] = n++;
  F0R(i, R) {
    F0R(j, 4) {
      V[i][j] = compress[V[i][j]];
    }
  }

  // edges 0..2R-1
  int N = 2 * R;
  vector<int> color(N);
  F0R(i, R) {
    color[2*i] = color[2*i+1] = i;
  }
  vector<array<int, 2>> edges;
  F0R(i, R) {
    edges.push_back({V[i][0], V[i][1]});
    edges.push_back({V[i][2], V[i][3]});
  }

  GraphMat m1(n, edges);
  ColorMat m2(N, color);
  MatroidIsect isect(m1, m2, N);
  auto ans = isect.solve();
  cout << 2*sz(ans) << '\n';
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  while (solve());
}
