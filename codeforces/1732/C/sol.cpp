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
  int N, Q; cin >> N >> Q;
  vector<int> A(N);
  vector<int> B;
  vector<int> v;
  vector<vector<int>> cnt(N, vector<int>(30, 0));
  F0R(i, N) {
    cin >> A[i];
    if (A[i]) {
      v.push_back(i);
      B.push_back(A[i]);
    }
    F0R(j, 30) {
      cnt[i][j] = i == 0 ? 0 : cnt[i-1][j];
      if (A[i] & (1 << j)) {
        cnt[i][j]++;
      }
    }
  }

  auto submask = [](int a, int b) {
    return (a & b) == a;
  };

  auto query = [&](int L, int R) -> pair<int, int> {
    pair<int, pair<int, int>> ans = {R - L, {L, R}};
    vector<int> C = cnt[R];
    F0R(j, 30) C[j] -= L == 0 ? 0 : cnt[L-1][j];
    int mask = 0;
    F0R(j, 30) if (C[j] & 1) mask += 1 << j;
    if (all_of(all(C), [](int i) {return i == 0;})) return {L, L};

    int sum = 0;
    auto idx = std::distance(v.begin(), lower_bound(all(v), L));
    auto idxR = std::distance(v.begin(), upper_bound(all(v), R));
    for (int i = idx; i < sz(B) && v[i] <= R; i++) {
      if (submask(sum, mask)) {
        ckmin(ans, {R - v[i], {v[i], R}});
      }

      int rsum = 0;
      for (int j = idxR-1; v[j] >= v[i]; j--) {
        if (!(sum & rsum) && submask(sum + rsum, mask)) {
          ckmin(ans, {v[j] - v[i], {v[i], v[j]}});
        }
        if (rsum & B[j]) break;
        rsum += B[j];
      }
      if (sum & B[i]) break;
      sum += B[i];
    }
    return ans.second;
  };

  while (Q--) {
    int L, R; cin >> L >> R;
    L--, R--;
    auto [l, r] = query(L, R);
    cout << l+1 << ' ' << r+1 << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
