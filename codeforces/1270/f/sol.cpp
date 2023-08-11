#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

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

const int maxn = 2e5;
const int B = 250;

int mp[maxn*B+maxn];
int vals[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  string s; cin >> s;
  int N = sz(s);
  vector<int> numZeros(N);
  F0R(i, N) {
    if (s[i] == '0') numZeros[i] = 1;
    if (i > 0) numZeros[i] += numZeros[i-1];
  }
  vector<pair<int, int>> ones;
  for (int i = 0; i < N; i++) {
    if (s[i] == '1') {
      int j = i+1;
      while (j < N && s[j] == '0') j++;
      ones.emplace_back(i, j-i-1);
      i = j-1;
    }
  }

  ll ans = 0;
  for (int k = 1; k <= B; k++) {
    mp[0 + maxn] = 1;
    int cur = 0;
    F0R(i, N) {
      if (s[i] == '1') cur += k-1;
      else cur--;
      vals[i] = cur;
      ans += mp[cur + maxn];
      mp[cur + maxn]++;
    }
    F0R(i, N) mp[vals[i] + maxn] = 0;
  }

  int idx = 0;
  F0R(i, N) {
    int j = 0;
    while (idx < sz(ones) && ones[idx].first < i) idx++;
    for (auto it = ones.begin() + idx; it != ones.end(); ++it) {
      j++;
      int l = it->second;
      int x = numZeros[it->first] - (i == 0 ? 0 : numZeros[i-1]);
      if (1LL * B * j - N > 0) break;
      int lb = max(B, (x + j - 1) / j);
      int ub = (x + l) / j;
      ans += max(0, ub - lb + 1);
    }
  }

  cout << ans << '\n';
}
