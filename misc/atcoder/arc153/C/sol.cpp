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
  int N; cin >> N;
  vector<int> A(N);
  for (auto& x: A) cin >> x;
  vector<int> B(N+1);
  F0Rd(i, N) B[i] = A[i] + B[i+1];
  vector<ll> b(N);
  // DEBUG(B);
  if (B[0] != 0) {
    ll s = std::accumulate(B.begin()+1, B.end(), 0LL);
    if (B[0] > 0) {
      b[0] = -s;
      FOR(i, 1, N) b[i] = B[0];
    }
    else {
      b[0] = s;
      FOR(i, 1, N) b[i] = -B[0];
    }
  }
  else {
    vector<int> pos, neg;
    F0R(i, N) {
      if (B[i] > 0) pos.push_back(i);
      else if (B[i] < 0) neg.push_back(i);
      else b[i] = 1;
    }
    if (pos.empty() || neg.empty()) {
      cout << "No\n";
      return 0;
    }
    else {
      F0R(i, N) {
        while (sz(pos) > 1 && sz(neg) > 1) {
          int i = pos.back(); pos.pop_back();
          int j = neg.back(); neg.pop_back();
          b[i] = -B[j];
          b[j] = B[i];
        }
      }
      ll s1 = 0;
      for (auto i: pos) s1 += B[i];
      ll s2 = 0;
      for (auto i: neg) s2 += B[i];

      for (auto i: pos) b[i] = -s2;
      for (auto i: neg) b[i] = s1;
    }
  }
  // DEBUG(b);

  cout << "Yes\n";
  ll sum = 0;
  const ll D = 1e12;
  F0R(i, N) {
    sum += b[i];
    // if (i > 0) assert(b[i] != 0);
    assert(abs(sum) <= D);
    cout << sum << ' ';
  }
  cout << '\n';
}
