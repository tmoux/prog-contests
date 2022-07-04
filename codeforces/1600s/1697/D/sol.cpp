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

char ask1(int i) {
  cout << "? 1" << ' ' << i << endl;
  char c; cin >> c;
  return c;
}

int ask2(int l, int r) {
  cout << "? 2" << ' ' << l << ' ' << r << endl;
  int x; cin >> x;
  return x;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  string ans(N+1, '#');
  int numfound = 0;
  for (int i = 1; i <= N; i++) {
    int x = ask2(1, i);
    if (x == numfound+1) {
      // new character, ask for it
      ans[i] = ask1(i);
      numfound++;
    }
    else {
      // old character, bin search for it
      vector<int> indices;
      set<char> seen;
      for (int j = i-1; j >= 1; j--) {
        if (!seen.count(ans[j])) {
          seen.insert(ans[j]);
          indices.push_back(j);
        }
      }
      int lo = -1, hi = sz(indices)-1;
      while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        int x = ask2(indices[mid], i);
        if (x == mid+1) hi = mid;
        else lo = mid;
      }
      ans[i] = ans[indices[hi]];
    }
  }
  cout << "! ";
  for (int i = 1; i <= N; i++) {
    cout << ans[i];
  }
  cout << endl;
}
