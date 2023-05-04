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

int R, C;
int ask(int r, int c) {
  cout << "? " << r << ' ' << c << endl;
  // int x; cin >> x;
  // return x;
  return max(abs(R - r), abs(C - c));
}

void answer(int r, int c) {
  cout << "! " << r << ' ' << c << endl;
  assert(r == R && c == C);
}

void solve() {
  int N, M; cin >> N >> M;
  cin >> R >> C;
  int a = ask(1, 1);
  int b = ask(1, M);

  if (a + b == M-1) {
    int c = ask(1, a+1);
    answer(c+1, a+1);
    return;
  }
  else if (a == b) {
    int c = ask(a+1, 1);
    answer(a+1, c+1);
    return;
  }
  int c = ask(N, 1);

  F0R(i1, 2) {
    F0R(i2, 2) {
      F0R(i3, 2) {
        int mnX = 1, mxX = N;
        int mnY = 1, mxY = M;

        if (i1 == 0) {
          ckmax(mnX, a+1);
          ckmin(mxX, a+1);
          ckmin(mxY, a+1);
        }
        else {
          ckmax(mnY, a+1);
          ckmin(mxY, a+1);
          ckmin(mxX, a+1);
        }

        if (i2 == 0) {
          ckmax(mnX, b+1);
          ckmin(mxX, b+1);
          ckmax(mnY, M-b);
        }
        else {
          ckmax(mnY, M-b);
          ckmin(mxY, M-b);
          ckmin(mxX, b+1);
        }

        if (i3 == 0) {
          ckmax(mnX, N-c);
          ckmin(mxX, N-c);
          ckmin(mxY, c+1);
        }
        else {
          ckmax(mnY, c+1);
          ckmin(mxY, c+1);
          ckmax(mnX, N-c);
        }

        if (mnX == mxX && mnY == mxY) {
          answer(mnX, mnY);
          return;
        }
      }
    }
  }
  assert(false);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
