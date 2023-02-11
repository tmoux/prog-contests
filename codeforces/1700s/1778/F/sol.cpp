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

// An operation can only increment prime factors we already have.
// If we do an operation, we might as well take the GCD of the subtree.
// In addition, it only makes sense to do operations from root to leaf, since switching the order never helps.
// We can imagine doing a postorder dfs, and on the way up, deciding whether to do an operation.
// The current value puts a bound on the GCD, so the max answer is A[1] * A[1].
// Use a dp[i][s] = min number of operations to make subtree i have gcd s (or a multiple of s).
// s is represented as a tuple of prime factors.
// Transitions are straightforward: consider either taking i, which costs 1, or not.
// Update the final answer when processing A[1] at the end.
// A[1] can only have 4 distinct prime numbers, so these are the only 4 we care about.
// The worst-case number is 2 * 3 * 5 * 7 = 210. In this case, we can have up to about
// 140 tuples of numbers that are less than 1000, or 260 including squares.
// So complexity is about O(N * 260).

using vi = vector<int>;
const int maxn = 1005;
int spf[maxn];

void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxn; i++) if (!spf[i]) {
    for (int j = i; j < maxn; j += i) {
      if (!spf[j]) spf[j] = i;
    }
  }
}

vi getDistinctPrimes(int x) {
  vector<int> v;
  while (x > 1) {
    int p = spf[x];
    v.push_back(p);
    while (x % p == 0) x /= p;
  }
  return v;
}

vi sqr(vi a) {
  for (auto& x: a) x *= 2;
  return a;
}

const int MX = 1000;
vector<vi> genStates(vi p) {
  int P = sz(p);
  vector<vi> ret;
  auto rec = y_combinator([&](auto rec, int i, vi v, int cur) -> void {
    if (i == P) {
      ret.push_back(v);
      ret.push_back(sqr(v));
      return;
    }
    int mult = 1;
    for (int j = 0; cur * mult <= MX; j++, mult *= p[i]) {
      v.push_back(j);
      rec(i+1, v, cur * mult);
      v.pop_back();
    }
  });
  rec(0, vi(), 1);
  sort(all(ret)); ret.erase(unique(all(ret)), ret.end());
  return ret;
}

vector<vi> states;
int S;

const int MS = 260;
bool Leq[MS][MS];
vi upd[MS];
map<vi, int> toIdx;
int sqrIdx[MS];

bool leq(const vi& a, const vi& b) {
  F0R(i, sz(a)) if (a[i] > b[i]) return false;
  return true;
};

void init() {
  states = genStates({2, 3, 5, 7});
  S = sz(states);
  F0R(i, S) toIdx[states[i]] = i;
  F0R(i, S) {
    if (toIdx.count(sqr(states[i]))) sqrIdx[i] = toIdx[sqr(states[i])];
  }
  F0R(i, S) {
    F0R(j, S) {
      Leq[i][j] = leq(states[i], states[j]);
    }
  }
  F0R(i, S) {
    F0R(j, S) {
      if (Leq[i][j]) {
        bool poss = true;
        F0R(k, S) {
          if (k == i || k == j) continue;
          if (Leq[i][k] && Leq[k][j]) {
            poss = false;
            break;
          }
        }
        if (poss) upd[i].push_back(j);
      }
    }
  }
}

int solve() {
  int N, K; cin >> N >> K;
  vector<vi> adj(N);
  vi A(N);
  F0R(i, N) cin >> A[i];
  REP(N-1) {
    int a, b; cin >> a >> b;
    --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vi ps = getDistinctPrimes(A[0]);
  int P = sz(ps);

  auto eval = [&](vi v) -> int {
    int res = 1;
    F0R(i, sz(v)) {
      REP(v[i]) res *= ps[i];
    }
    return res;
  };

  int ans = A[0];
  const ll INF = 1e5+5;
  vector<vector<ll>> dp(N, vector<ll>(S, INF));
  y_combinator([&](auto dfs, int i, int p) -> void {
    for (int j: adj[i]) {
      if (j != p) {
        dfs(j, i);
      }
    }
    vi si(4);
    {
      int x = A[i];
      F0R(j, P) {
        while (x % ps[j] == 0) {
          x /= ps[j], si[j]++;
        }
      }
    }
    int sii = toIdx[si];
    F0R(s, S) {
      if (Leq[s][sii]) {
        ll add = 0;
        for (int j: adj[i]) {
          if (j != p) add += dp[j][s];
        }
        ckmin(dp[i][s], min(INF, add));
        ckmin(dp[i][sqrIdx[s]], min(INF, 1 + add));
        if (i == 0 && 1 + add <= K) {
          ckmax(ans, A[i] * eval(states[s]));
        }
      }
    }
    // update lattice
    F0Rd(j, S) {
      for (auto s: upd[j]) {
        ckmin(dp[i][j], dp[i][s]);
      }
    }
  })(0, 0);
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  init();
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
