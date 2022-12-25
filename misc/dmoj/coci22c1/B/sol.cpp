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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, Q; cin >> N >> Q;
  vector<ll> C(N);
  for (auto& x: C) cin >> x;
  sort(all(C));
  vector<ll> pfx(N), sfx(N);
  for (int i = 0; i < N; i++) {
    pfx[i] = C[i];
    if (i > 0) pfx[i] += pfx[i-1];
  }
  for (int i = N-1; i >= 0; i--) {
    sfx[i] = C[i];
    if (i + 1 < N) sfx[i] += sfx[i+1];
  }

  F0R(i, Q) {
    int k, m; cin >> k >> m;

    auto query = [&](int i, ll& tr) {
      if (i != -1 && C[i] > k) return;
      // cout << "querying " << i << endl;
      int j = N - (m - (i + 1));
      if (j < N && C[j] < k) return;
      ll ans = 0;
      if (i >= 0) ans += pfx[i];
      if (j < N) ans += (2LL * k * (N - j)) - sfx[j];
      ckmin(tr, ans);
    };

    ll lo = -1e12, hi = 1e12;
    while (lo + 1 < hi) {
      ll B = (lo + hi) / 2;

      int cnt = 0;
      auto it = upper_bound(all(C), B);
      cnt += distance(C.begin(), it);

      auto it2 = lower_bound(all(C), 2*k - B);
      cnt += min(distance(it, C.end()), distance(it2, C.end()));

      if (cnt >= m) {
        hi = B;
      }
      else lo = B;
    }
    
    ll B = hi;
    ll tr = 1e18;
    if (B < C[0]) query(-1, tr);
    else {
      auto it = lower_bound(all(C), B);
      int i = distance(C.begin(), it);
      if (*it > B) i--;

      for (int j = max(-1, i - 200); j < min(N, i + 200); j++) {
        query(j, tr);
      }
    }

    /*
    for (int i = -1; i < m && C[i] <= k; i++) {
      query(i, tr);
    }
    */

    cout << tr << '\n';
  }
}
