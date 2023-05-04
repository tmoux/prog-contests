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

struct Sparse
{
    static const int mk = 19;
    ll* tb[mk];
    static inline int lg(int x) { return 32 - __builtin_clz(x) - 1; }
    Sparse(const vector<ll>& a, int n) {
        for (int i = 0; i < mk; i++) {
          tb[i] = new ll[n];
        }
        for (int i = 0; i < n; i++) tb[0][i] = a[i];
        for (int k = 1; k <= lg(n); k++) {
            for (int i = 0; i < n; i++) {
                int nx = i + (1<<(k-1));
                if (nx < n) tb[k][i] = min(tb[k-1][i],tb[k-1][nx]);
                else tb[k][i] = tb[k-1][i];
            }
        }
    }
    int getmin(int l, int r) {
        int g = lg(r-l+1);
        return min(tb[g][l],tb[g][r-(1<<g)+1]);
    }
};


void solve() {
  int N; cin >> N;
  vector<ll> A(N), D(N), P(N);
  F0R(i, N) {
    cin >> A[i];
    D[i] = i == 0 ? A[i] : A[i] - A[i-1];
    P[i] = D[i];
    if (i-2 >= 0) P[i] += P[i-2];
  }

  vector<map<ll, vector<int>>> mp(2);
  vector<vector<ll>> Ps(2, vector<ll>(N, LLONG_MAX));
  F0R(i, N) {
    Ps[i&1][i] = P[i];
    mp[i&1][P[i]].push_back(i);
  }
  array<Sparse, 2> st = {Sparse(Ps[0], N), Sparse(Ps[1], N)};

  auto countlen = [&](int i, int l, int r, ll p) -> int {
    if (!mp[i&1].count(p)) return 0;
    return std::distance(lower_bound(all(mp[i&1][p]), l),
                         upper_bound(all(mp[i&1][p]), r));
  };
  auto getlen = [&](int i, ll p) -> int {
    int lo = i, hi = N;
    while (lo + 1 < hi) {
      int mid = (lo + hi) / 2;
      if (st[i&1].getmin(i, mid) >= p) {
        lo = mid;
      }
      else hi = mid;
    }
    if (((N-1)&1) == (i&1) && lo == N-1) return lo;
    else return lo-1;
  };

  ll total = 0;
  F0R(i, N-1) {
    // odd length: sum1 = 0, sum2 >= 0
    int r1 = getlen(i, P[i] - A[i]);
    int r2 = getlen(i+1, P[i+1] - D[i+1]);
    int r = min(r1, r2+1);

    total += countlen(i, i, r, P[i]-A[i]);
    // even length: sum1 >= 0, sum2 = 0

    r = min(r1+1, r2);
    total += countlen(i+1, i+1, r, P[i+1]-D[i+1]);
  }
  if (A[N-1] == 0) total++;

  cout << total << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
