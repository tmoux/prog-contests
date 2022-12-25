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

int hamming(string a, string b) {
  int r = 0;
  F0R(i, sz(a)) r += a[i] != b[i];
  return r;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int M; cin >> M;
  double eps; cin >> eps;

  int N = M; // idk
  vector<string> graphs(M);

  cout << N << '\n';
  F0R(i, M) {
    for (int a = 0; a < N; a++) {
      for (int b = a+1; b < N; b++) {
        if (a == i) {
          graphs[i] += '1';
        }
        else graphs[i] += '0';
      }
    }
    F0R(j, N*(N-1)/2) {
      char c = rng() & 1 ? '1' : '0';
      graphs[i] += c;
    }
    cout << graphs[i] << endl;
  }

  const int Q = 100;
  REP(Q) {
    string h; cin >> h;
    pair<int, int> best = {N*(N-1)/2, -1};
    F0R(i, M) {
      int d = hamming(graphs[i], h);
      ckmin(best, {d, i});
    }
    cout << i << endl;
  }
}
