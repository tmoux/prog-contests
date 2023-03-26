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
  int N, K; cin >> N >> K;
  vector<int> A(2*N), B(2*N);
  F0R(i, N) {
    cin >> A[i];
    A[i+N] = A[i];
  }
  vector<int> ones;
  F0R(i, N) {
    cin >> B[i];
    B[i+N] = B[i];
    if (B[i] == 1) {
      ones.push_back(i);
      ones.push_back(i+N);
    }
  }
  vector<ll> pfx(2*N);
  F0R(i, 2*N) pfx[i] = A[i] + (i == 0 ? 0 : pfx[i-1]);
  auto getsum = [&](int l, int r) -> ll {
    if (r == 0) return 0LL;
    return pfx[r-1] - (l == 0 ? 0 : pfx[l-1]);
  };

  if (ones.empty()) {
    ll total = getsum(0, N);
    F0R(i, N) {
      cout << 2*total << ' ';
    }
    cout << '\n';
    return;
  }
  else {
    using pii = pair<ll, ll>;
    const int maxk = 18;
    vector<vector<int>> jmp(maxk, vector<int>(2*N, -1));
    vector<vector<pii>> cost(maxk, vector<pii>(2*N));
    // (cost (not including initial), new h)
    sort(all(ones));
    F0R(i, sz(ones)) {
      if (i + 1 < sz(ones)) {
        jmp[0][ones[i]] = ones[i+1];
        ll c = getsum(ones[i], ones[i+1]);
        cost[0][ones[i]] = {max(0LL, c - K) * 2, max(0LL, K - c)};
      }
    }
    FOR(k, 1, maxk) {
      for (int i: ones) {
        if (jmp[k-1][i] == -1 || jmp[k-1][jmp[k-1][i]] == -1) {
          jmp[k][i] = -1;
        }
        else {
          int j = jmp[k-1][i];
          jmp[k][i] = jmp[k-1][j];
          auto [c1, h1] = cost[k-1][i];
          auto [c2, h2] = cost[k-1][j];
          cost[k][i] = {c1 + (K - h1) + c2, h2};
        }
      }
    }

    F0R(i, N) {
      ll C = 0;
      int h = 0;

      int j = *lower_bound(all(ones), i);
      // i -> 1
      ll c = getsum(i, j);
      C += 2 * c;

      // 1 -> 1'
      F0Rd(k, maxk) {
        if (jmp[k][j] != -1 && jmp[k][j] <= i + N) {
          C += K - h;
          h = K;
          C += cost[k][j].first;
          h = cost[k][j].second;
          j = jmp[k][j];
        }
      }

      // 1' -> i + N
      C += K - h;
      h = K;
      c = max(0LL, getsum(j, i + N) - h);
      C += 2 * c;
      h = max(0LL, h - getsum(j, i + N));

      C -= h;

      cout << C << ' ';
    }
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
