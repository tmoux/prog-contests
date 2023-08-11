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
int N, Q;
int A[maxn];
int pre[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> Q;
  map<int, vector<int>> mp[2];
  vector<int> nonzeros;
  for (int i = 1; i <= N; i++) {
    cin >> A[i];
    pre[i] = A[i] ^ pre[i-1];
    mp[i&1][pre[i]].push_back(i);
    if (A[i] != 0) nonzeros.push_back(i);
  }

  auto query = [&](int l, int r) -> int {
    auto it = lower_bound(all(nonzeros), l);
    if (it == nonzeros.end() || *it > r) return 0;
    else if ((pre[r] ^ pre[l-1]) != 0) return -1;
    else if ((r - l + 1) % 2 == 1 || A[l] == 0 || A[r] == 0) return 1;
    else {
      int d = ((l-1) & 1) ^ 1;
      it = lower_bound(all(mp[d][pre[l-1]]), l);
      if (it != mp[d][pre[l-1]].end() && *it <= r) return 2;
      else return -1;
    }
  };
  while (Q--) {
    int l, r; cin >> l >> r;
    cout << query(l, r) << '\n';
  }
}
