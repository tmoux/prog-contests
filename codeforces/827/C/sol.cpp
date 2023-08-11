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

template<typename T, T (*init)()>
struct Fenwick
{
  int n;
  vector<T> bit;
  Fenwick(int n_) {
    n = n_;
    bit.resize(n+1, init());
  }
  void add(int i, T x) {
    for (; i <= n; i += i & (-i))
      bit[i] += x;
  }

  T sum(int i) {
    T r = init();
    for (; i; i -= i & (-i)) {
      r += bit[i];
    }
    return r;
  }
};
using T = array<int, 4>;
T& operator+=(T& a, T b) {
  F0R(i, 4) a[i] += b[i];
  return a;
}
T& operator-=(T& a, T b) {
  F0R(i, 4) a[i] -= b[i];
  return a;
}

const int maxn = 1e5+5;
int N, Q;
string S;

T init() {
  return {0, 0, 0, 0};
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  map<char, int> mp = {
    {'A', 0},
    {'T', 1},
    {'G', 2},
    {'C', 3},
  };
  cin >> S >> Q;
  N = sz(S);

  const int B = 10;
  vector<vector<Fenwick<T, init>>> Fens(B+1);
  for (int i = 1; i <= B; i++) {
    for (int j = 0; j < i; j++) {
      Fens[i].push_back(Fenwick<T, init>(N / i + 1));
    }
  }


  auto adds = [&](char c) {
    T add = {0, 0, 0, 0}; add[mp[c]] = 1;
    return add;
  };
  auto nadds = [&](char c) {
    T add = {0, 0, 0, 0}; add[mp[c]] = -1;
    return add;
  };

  auto index = [&](int i, int j, int b) {
    return (i - j) / b + 1;
  };

  auto update = [&](int i, char c, bool init = false) -> void {
    for (int b = 1; b <= B; b++) {
      int j = i % b;
      if (!init) Fens[b][j].add(index(i, j, b), nadds(S[i]));
      Fens[b][j].add(index(i, j, b), adds(c));
    }
    S[i] = c;
  };

  F0R(i, N) {
    update(i, S[i], true);
  }

  auto leq_index = [&](int i, int b, int j) {
    if (i % b >= j) {
      return i - ((i % b) - j);
    }
    else {
      return i - (b - (j - (i % b)));
    }
  };

  while (Q--) {
    int t; cin >> t;
    if (t == 1) {
      int i; cin >> i; i--;
      char c; cin >> c;
      update(i, c);
    }
    else {
      int l, r; cin >> l >> r;
      l--, r--;
      string e; cin >> e;
      int b = sz(e);

      int ans = 0;
      F0R(i, b) {
        int j = (l + i) % b;
        int x = mp[e[i]];

        int R = leq_index(r, b, j);
        if (l <= R) {
          int L = leq_index(l-1, b, j);
          T add = Fens[b][j].sum(index(R, j, b));
          if (L >= 0) add -= Fens[b][j].sum(index(L, j, b));
          ans += add[x];
        }
      }

      cout << ans << '\n';
    }
  }
}
