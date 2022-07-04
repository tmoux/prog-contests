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
  int N, Q, X; cin >> N >> Q >> X;
  vector<int> W(2*N);
  ll total = 0;
  F0R(i, N) {
    cin >> W[i];
    W[i+N] = W[i];
    total += W[i];
  }

  vector<ll> num(N);
  const int MX = 40;
  vector<vector<int>> jmp(MX, vector<int>(N));
  {
    ll sum = 0;
    int j = 0;
    F0R(i, N) {
      if (i > 0) sum -= W[i-1];
      while (sum < (X % total)) {
        sum += W[j++];
      }
      jmp[0][i] = j % N;

      num[i] = 1LL * N * (X / total) + j-i;
    }

    /*
    F0R(i, N) {
      cout << i << ": " << jmp[0][i] << endl;
    }
    */

    for (int k = 1; k < MX; k++) {
      F0R(i, N) {
        jmp[k][i] = jmp[k-1][jmp[k-1][i]];
      }
    }
  }

  REP(Q) {
    ll K; cin >> K; K--;
    int cur = 0;
    F0Rd(i, MX) {
      if (K & (1LL << i)) {
        cur = jmp[i][cur];
      }
    }
    cout << num[cur] << '\n';
  }
}
