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

int ask(int X, int Y) {
  cout << "? " << X << ' ' << Y << endl;
  int d; cin >> d;
  return d;
}

void answer(int A, int B, int C, int D) {
  cout << "! " << A << ' ' << B << ' ' << C << ' ' << D << endl;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;
  if (M == 1) {
    assert(M == 1);
    int a = ask(1, M);
    int b = ask(N, M);

    answer(1 + a, M, N - b, M);
  }
  else {
    int A = ask(1, 1);
    int B = ask(1, M);
    int C = ask(N, 1);
    int D = ask(N, M);

    auto div2 = [&](int x) {
      return x >= 0 && x % 2 == 0;
    };
    auto in_bounds = [&](int x, int y) -> bool {
      return 1 <= x && x <= N && 1 <= y && y <= M;
    };
    // case 1:
    bool poss1 = true;
    int x1, y1, x2, y2;
    if (div2(A + C - (N - 1))) {
      int d = (A + C - (N - 1)) / 2;
      y1 = 1 + d;
      x1 = 1 + (A - d);
    }
    else poss1 = false;
    if (div2(B + D - (N - 1))) {
      int d = (B + D - (N - 1)) / 2;
      y2 = M - d;
      x2 = 1 + (B - d);
    }
    else poss1 = false;
    poss1 &= in_bounds(x1, y1) && in_bounds(x2, y2);

    if (poss1 && ask(x1, y1) == 0) {
      answer(x1, y1, x2, y2);
    }
    else {
      assert(div2(A + B - (M - 1)));
      int d = (A + B - (M - 1)) / 2;
      x1 = 1 + d;
      y1 = 1 + (A - d);

      assert(div2(C + D - (M - 1)));
      d = (C + D - (M - 1)) / 2;
      x2 = N - d;
      y2 = 1 + (C - d);

      answer(x1, y1, x2, y2);
    }
  }
}
