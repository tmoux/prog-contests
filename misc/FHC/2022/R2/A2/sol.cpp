#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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

template <class K, class V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<K, V, std::less<K>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

int solve() {
  int N; cin >> N;
  vector<int> S(N);
  F0R(i, N) {
    cin >> S[i];
  }

  vector<ordered_set<int>> sets(1e6+6);

  F0R(i, N) {
    sets[S[i]].insert(i);
  }

  auto get_count = [&](int c, int l, int r) -> int {
    int R = sets[c].order_of_key
    // return segs[c-'a'].prod(l, r);
  };

  int ans = 0;
  int Q; cin >> Q;
  REP(Q) {
    int t; cin >> t;
    if (t == 1) {
      int i, x; cin >> i >> x;
    }
    else {
      int L, R; cin >> L >> R;
      L--; R--;

      vector<int> mp(26, 0);
      int num_odd = 0;
      for (char c = 'a'; c <= 'z'; c++) {
        mp[c] += get_count(c, L, R);
        if (mp[c-'a'] % 2 == 1) num_odd++;
      }

      auto check = [&](int l, int r) -> bool {
        for (char c = 'a'; c <= 'z'; c++) {
          if (get_count(c, l, r) != mp[c-'a']/2) return false;
        }
        return true;
      };

      bool poss = num_odd == 1;
      if (poss) {
        int len = (R-L+1)/2;
        poss = check(L, L+len-1) || check(R-len+1, R);
      }

      if (poss) ans++;
    }
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": " << solve() << '\n';
  }
}
