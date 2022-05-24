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

const int maxn = 100;
int N;
int a[maxn];

int b[maxn];

set<int> poss[maxn];

bool valid() {
  F0R(i, N) {
    if (min(b[(i+1)%N], b[(i-1+N)%N]) != a[i]) {
      return false;
    }
  }
  return true;
}


void rec(int i) {
  if (i == N) {
    if (valid()) {
      F0R(j, N) {
        poss[j].insert(b[j]);
      }
    }
  }
  else {
    if (b[i] != 0) rec(i+1);
    else {
      for (int d = 1; d <= N; d++) {
        b[i] = d;
        rec(i+1);
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  T = 100;
  while (T--) {
    cin >> N;
    F0R(i, N) poss[i].clear();
    F0R(i, N) cin >> a[i];
    F0R(i, N) a[i] = 1;
    for (int mask = 0; mask < (1<<N); mask++) {
      F0R(i, N) b[i] = 0;
      F0R(i, N) {
        if (mask & (1<<i)) {
          b[(i-1+N)%N] = a[i];
        }
        else {
          b[(i+1)%N] = a[i];
        }
      }
      rec(0);
    }

    F0R(i, N) {
      if (i > 0) cout << ' ';
      if (sz(poss[i]) == 1) {
        cout << *poss[i].begin();
      }
      else {
        cout << 0;
      }
    }
    cout << '\n';
    /*
    F0R(i, N) {
      cout << i << ": " << poss[i] << endl;
    }
    */
  }
}

