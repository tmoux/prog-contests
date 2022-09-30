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

struct S {
  int ai;
  int k;

  int get_next(int x) {
    while (ai/k >= x) {
      k = ai/(ai/k)+1;
    }
    return ai/k;
  }
};

int solve() {
  int N, K; cin >> N >> K;
  const int maxn = 1e5+5;
  vector<vector<int>> cnt(maxn);
  vector<int> A(N);
  vector<S> v(N);
  int mn = 2e9;
  F0R(i, N) {
    cin >> A[i];
    v[i] = {A[i], 1};
    cnt[A[i]].push_back(i);
    ckmin(mn, A[i]);
  }

  int ans = 2e9;
  for (int x = 100000; x >= 0; x--) {
    ckmin(ans, x - mn);

    if (x > 0) {
      for (auto i: cnt[x]) {
        int next_index = v[i].get_next(x);  
        if (v[i].k > K) goto done;
        ckmin(mn, next_index);
        cnt[next_index].push_back(i);
      }
      cnt.pop_back();
    }
  }

  done:
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
