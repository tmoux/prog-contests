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
  int N, M; cin >> N >> M;

  /*
  if (N <= 19) {
    cout << 7 << '\n';
    cout << "2 3 16 4 8 5 13\n";
    return 0;
  }
  vector<int> v = {1, 2, 3};
  for (int i = 7; i <= N; i += 7) {
    if (i > 7) v.push_back(i-1);
    v.push_back(i);
  }
  if (v.back() + 3 < N) {
    if (v[sz(v)-1] != N-1 && v[sz(v)-2] != N-1) v.push_back(N-1);
    if (v[sz(v)-1] != N && v[sz(v)-1] != N) v.push_back(N);
  }
  */

  int s = N/2+1;
  vector<int> v = {s};
  for (int i = 1; i <= M-1; i++) {
    v.push_back(i&1 ? s - i : s + i);
  }

  auto check = [&](const vector<int> v) -> bool {
    set<int> s;
    F0R(i, sz(v)) {
      F0R(j, sz(v)) {
        if (i == j) continue;
        int x = v[i], y = v[j];
        // s.insert(x+y);
        // s.insert(x-y);
        if (1 <= x+y && x+y <= N) s.insert(x+y);
        if (1 <= x-y && x-y <= N) s.insert(x-y);
      }
    }
    cout << v << endl;
    cout << s << endl;
    for (int i = 1; i <= N; i++) assert(s.count(i));
    return true;
  };
  for (auto x: v) assert(1 <= x && x <= N);
  // assert(sz(v) <= M);
  // assert(sz(v) <= (int)(0.4 * N));
  assert(check(v));

  cout << sz(v) << '\n';
  F0R(i, sz(v)) {
    cout << v[i] << " \n"[i == sz(v)-1];
  }

  return 0;
  /*
  for (int i = 1, inc = 1; i <= N; i += inc, inc++) {
    v.push_back(i);
  }

  vector<int> v = {1, 2, 3};
  for (int i = 7; i <= N; i += 7) v.push_back(i);
  v.push_back(N-1);
  v.push_back(N);
  cout << v << endl;
  cout << check(v) << endl;
  cout << sz(v) << ' ' << (int)(0.4 * N) << endl;


  return 0;
  */

  /*
  vector<int> v;
  FOR(i1, 1, N+1)
    FOR(i2, 1, N+1)
    FOR(i3, 1, N+1)
    FOR(i4, 1, N+1)
    FOR(i5, 1, N+1)
    FOR(i6, 1, N+1) {
    if (i1 <= i2 && i2 <= i3 && i3 <= i4 && i4 <= i5 && i5 <= i6) {
      v = {i1, i2, i3, i4, i5, i6};
      if (sz(v) == M && check(v)) {
        cout << v << endl;
      }
    }
  }
  */
  // cout << v << endl;
  // cout << s << endl;
  // assert(sz(s) == N);
}
