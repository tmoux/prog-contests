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

int N;
bool is_sorted(vector<int>& v) {
    F0R(i, sz(v)) {
        if (v[i] != i) return false;
    }
    return true;
}

void f1(vector<int>& v) {
    sort(v.begin(), v.begin() + 2 * N);
}

void f2(vector<int>& v) {
    sort(v.begin() + N, v.end());
}

int ops1(vector<int> v) {
    int r = 0;
    while (true) {
        if (is_sorted(v)) break;
        f1(v), r++;
        if (is_sorted(v)) break;
        f2(v), r++;
    }
    return r;
}

int ops2(vector<int> v) {
    int r = 0;
    while (true) {
        if (is_sorted(v)) break;
        f2(v), r++;
        if (is_sorted(v)) break;
        f1(v), r++;
    }
    return r;
}

int A = 0, O = 0;
bool check2(vector<int> v) {
    bool b1 = true, b2 = true;
    F0R(i, N) if (v[i] >= 2*N) b1 = false;
    for (int i = 2*N; i < 3*N; i++) if (v[i] < N) b2 = false;
    if (b1) A++;
    if (b1 && b2) O++;
    return b1 && b2;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  vector<int> p(3 * N);
  iota(all(p), 0);

  map<int, vector<vector<int>>> mp;
  int c2 = 0;
  do {
      int a = ops1(p);
      int b = ops2(p);
      mp[min(a, b)].push_back(p);
      assert(min(a, b) <= 3);
      check2(p);
      // if (check2(p)) c2++;
  } while (next_permutation(all(p)));

  for (auto [x, vv]: mp) {
      // cout << x << ": " << '\n';
      cout << x << ": " << sz(vv) << endl;
      continue;
      for (auto v : vv) {
          cout << v << endl;
      }
  }

  DEBUG(A);
  DEBUG(O);

}
