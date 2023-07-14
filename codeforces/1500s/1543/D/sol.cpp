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

const int MX = 30;
struct Num {
  int K;
  vector<int> v;
  Num(int _K) : K(_K) {
    v.resize(MX, 0);
  }

  int toDecimal() {
    int r = 0, mult = 1;
    F0R(i, MX) {
      r += mult * v[i];
      mult *= K;
    }
    return r;
  }

  Num operator^(Num b) {
    Num r(K);
    F0R(i, MX) {
      r.v[i] = (v[i] + b.v[i]) % K;
    }
    return r;
  }

  Num operator-() {
    Num r(K);
    F0R(i, MX) {
      r.v[i] = (K - v[i]) % K;
    }
    return r;
  }
};

Num fromDecimal(int x, int K) {
  Num r(K);
  int i = 0;
  while (x > 0) {
    r.v[i++] = x % K;
    x /= K;
  }
  return r;
}

int K;
Num ANS(2);

int query(int x) {
  cout << x << endl;
  // if (x == ANS.toDecimal()) {
  //   return 1;
  // }
  // else {
  //   // cout << "guessed " << fromDecimal(x, K).v << ", now ans is " << ANS.v << endl;
  //   ANS = fromDecimal(x, K) ^ (-ANS);
  //   return 0;
  // }
  int r; cin >> r;
  return r;
}

void solve() {
  int N; cin >> N;
  cin >> K;

  // int z; cin >> z;
  // ANS = fromDecimal(z, K);

  Num sum(K);
  F0R(x, N) {
    Num nsum = sum ^ (x % 2 == 0 ? (fromDecimal(x, K)) : -fromDecimal(x, K));
    // cout << "from dec " << fromDecimal(x, K).v << ' ' << (-fromDecimal(x, K)).v << endl;
    // cout << "sum " << sum.v << endl;
    // cout << "query " << nsum.v << endl;
    if (query(nsum.toDecimal())) return;
    sum = nsum ^ (-sum);
  }
  assert(false);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
