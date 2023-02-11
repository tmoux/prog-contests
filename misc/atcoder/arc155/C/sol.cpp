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
int N, A[maxn], B[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  vector<int> odds, bodds;
  F0R(i, N) {
    cin >> A[i];
    if (A[i]&1) odds.push_back(i);
  }
  F0R(i, N) {
    cin >> B[i];
    if (B[i]&1) bodds.push_back(i);
  }

  bool poss = false;
  for (int i = 0; i + 1 < sz(odds); i++) {
    if (odds[i+1] - odds[i] <= 2) {
      poss = true;
    }
  }

  if (!poss) {
    bool p = true;
    for (auto i: odds) if (A[i] != B[i]) p = false;
    odds.push_back(-1);
    odds.push_back(N);
    sort(all(odds));
    for (int i = 0; i + 1 < sz(odds); i++) {
      vector<int> u, v;
      for (int k = odds[i] + 1; k < odds[i+1]; k++) {
        // cout << "idx " << k << endl;
        u.push_back(A[k]);
        v.push_back(B[k]);
      }
      sort(all(u));
      sort(all(v));
      // cout << u << ' ' << v << endl;
      if (!(u == v)) p = false;
    }
    cout << (p ? "Yes" : "No") << '\n';
  }
  else {
    bool bposs = false;
    for (int i = 0; i + 1 < sz(bodds); i++) {
      if (bodds[i+1] - bodds[i] <= 2) {
        bposs = true;
      }
    }
    cout << (bposs ? "Yes" : "No") << '\n';
  }
}
