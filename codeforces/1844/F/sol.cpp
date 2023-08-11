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
  int N, c; cin >> N >> c;
  vector<int> A(N);
  F0R(i, N) cin >> A[i];
  if (c >= 0) {
    sort(all(A));
    for (auto x: A) cout << x << ' ';
    cout << '\n';
  }
  else {
    auto F = [&](int x, int y) -> ll {
      return abs(y - x - c);
    };
    auto calc = [&](vector<int> v) -> ll {
      ll ans = 0;
      FOR(i, 1, N) {
        ans += F(v[i-1], v[i]);
      }
      return ans;
    };
    auto sorted = A; sort(all(sorted), greater<int>());
    ll minSum = calc(sorted);

    vector<int> ans;
    ll curSum = 0;
    multiset<int> ms; for (auto x: A) ms.insert(x);
    ll setSum = 0;
    FOR(i, 1, N) {
      setSum += F(sorted[i-1], sorted[i]);
    }
    REP(N) {
      bool done = false;
      // DEBUG(ans);
      // DEBUG(ms);
      // DEBUG(curSum);
      for (auto it = ms.begin(); it != ms.end(); ++it) {
        ll nCurSum = curSum;
        ll nSetSum = setSum;
        if (next(it) != ms.end()) {
          nSetSum -= F(*next(it), *it);
        }
        if (it != ms.begin()) {
          nSetSum -= F(*it, *prev(it));
        }
        if (it != ms.begin() && next(it) != ms.end()) {
          nSetSum += F(*next(it), *prev(it));
        }
        if (!ans.empty()) nCurSum += F(ans.back(), *it);

        ll tr = nCurSum + nSetSum;
        if (sz(ms) > 1) {
          if (it == prev(ms.end())) {
            tr += F(*it, *prev(prev(ms.end())));
          }
          else {
            tr += F(*it, *prev(ms.end()));
          }
        }
        // cout << "trying " << *it << ": " << tr << endl;
        if (tr == minSum) {
          // add it
          curSum = nCurSum;
          setSum = nSetSum;
          ans.push_back(*it);
          ms.erase(it);
          done = true;
          break;
        }
      }
      assert(done);
    }
    for (auto x: ans) {
      cout << x << ' ';
    }
    cout << '\n';
  }
  // auto sorted = A; sort(all(sorted), greater<int>());
  // // cout << sorted << endl;
  // // cout << calc(sorted) << endl;

  // int ans = 1e9;
  // auto p = A; sort(all(p));
  // do {
  //   cout << p << ": " << calc(p) << endl;
  //   ckmin(ans, calc(p));
  // } while (next_permutation(all(p)));
  // DEBUG(ans);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
