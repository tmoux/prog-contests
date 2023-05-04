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

const int maxn = 2e5+5;
int N, M;
const int BLK = 400;
int X[maxn], Y[maxn];

int on[maxn], pfx[maxn];
int c[BLK][BLK];

bool notInMaintenance(int i, int s, int t) {
  return (t - s) % (X[i] + Y[i]) < X[i];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  FOR(i, 1, N+1) {
    cin >> X[i] >> Y[i];
  }
  memset(on, -1, sizeof on);

  int total = 0;
  int cur = 0;
  F0R(t, M) {
    int op, k; cin >> op >> k;
    int d = X[k] + Y[k];
    if (op == 1) {
      total++;
      if (d < BLK) {
        int s = t % d;
        for (int i = 0; i < X[k]; i++) {
          c[d][(s+i)%d]++;
        }
      }
      else {
        for (int i = t; i < M; i += d) {
          pfx[i]++;
          if (i+X[k] < M) pfx[i+X[k]]--;
        }
      }
      on[k] = t;
    }
    else {
      total--;
      if (d < BLK) {
        int s = on[k] % d;
        for (int i = 0; i < X[k]; i++) {
          c[d][(s+i)%d]--;
        }
      }
      else {
        if (notInMaintenance(k, on[k], t-1)) {
          cur--;
        }
        for (int i = on[k]; i < M; i += d) {
          pfx[i]--;
          if (i+X[k] < M) pfx[i+X[k]]++;
        }
      }
      on[k] = -1;
    }

    cur += pfx[t];
    int ans = cur;
    FOR(i, 1, BLK) {
      ans += c[i][t%i];
    }
    cout << total-ans << '\n';
  }
}
