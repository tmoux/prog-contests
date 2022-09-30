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

int ask(int a, int b) {
  cout << "? " << a << ' ' << b << endl;
  int x; cin >> x;
  assert(x != -1);
  return x;
}

void answer(int x) {
  cout << "! " << x << endl;
  return;
}

void solve() {
  int N; cin >> N;
  vector<int> v(1<<N);
  iota(all(v), 1);
  while (true) {
    if (sz(v) == 1) {
      answer(v[0]);
      return;
    }
    else if (sz(v) == 2) {
      int a = v[0], b = v[1];
      int z = ask(a, b);
      assert(z == 1 || z == 2);
      answer(z == 1 ? a : b);
      return;
    }
    else {
      assert(sz(v) % 4 == 0);
      auto get_winner = [&](int a, int b, int c, int d) -> int {
        int z = ask(a, c);
        if (z == 0) {
          z = ask(b, d);
          assert(z == 1 || z == 2);
          return z == 1 ? b : d;
        }
        else {
          if (z == 1) {
            // compare a and d
            z = ask(a, d);
            return z == 1 ? a : d;
          }
          else {
            // compare b and c
            z = ask(b, c);
            return z == 1 ? b : c;
          }
        }
      };

      vector<int> nv;
      for (int i = 0; i < sz(v); i += 4) {
        int a = v[i];
        int b = v[i+1];
        int c = v[i+2];
        int d = v[i+3];
        
        nv.push_back(get_winner(a, b, c, d));
      }
      v = nv;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
