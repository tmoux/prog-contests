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
  int N; cin >> N;
  vector<pair<ll, ll>> v(N);
  ll total = 0;
  ll mxR = 0, mxC = 0;
  F0R(i, N) {
    ll a, b; cin >> a >> b;
    v[i] = {a, b};
    total += a * b;
    ckmax(mxR, a);
    ckmax(mxC, b);
  }

  auto check = [&](ll R, ll C) -> bool {
    multiset<pair<ll, ll>> A, B;
    for (auto [a, b]: v) {
      A.insert({a, b});
      B.insert({b, a});
    }

    while (!A.empty()) {
      auto [x, y] = *prev(A.end());
      if (x == R && y <= C) {
        C -= y;
        A.erase(prev(A.end()));
        auto it = B.find({y, x});
        B.erase(it);
      }
      else {
        tie(y, x) = *prev(B.end());
        if (y == C && x <= R) {
          R -= x;
          B.erase(prev(B.end()));
          auto it = A.find({x, y});
          A.erase(it);
        }
        else return false;
      }
    }
    return true;
  };
  // DEBUG(mxR);
  // DEBUG(mxC);
  // DEBUG(total);

  vector<pair<ll, ll>> ans;
  if (total % mxR == 0) {
    if (check(mxR, total/mxR)) ans.push_back({mxR, total/mxR});
  }
  if (total % mxC == 0) {
    if (check(total/mxC, mxC)) ans.push_back({total/mxC, mxC});
  }

  sort(all(ans)); ans.erase(unique(all(ans)), ans.end());


  assert(!ans.empty());
  cout << sz(ans) << '\n';
  for (auto [a, b]: ans) {
    cout << a << ' ' << b << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
