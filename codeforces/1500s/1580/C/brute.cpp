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
const int BLK = 1000;
int X[maxn], Y[maxn];

int on[maxn], cur[maxn], pfx[maxn];
int c[BLK][BLK];
int total = 0;
set<pair<int, int>> S, T;

bool inMaintenance(int i, int s, int t) {
  return (t - s) % (X[i] + Y[i]) < X[i];
}

void rebuild() {
  S.clear();
  T.clear();
  memset(c, 0, sizeof c);
  memset(pfx, 0, sizeof pfx);
  FOR(i, 1, N+1) {
    if (on[i] >= 0) {
      int d = X[i] + Y[i];
      int s = on[i] % d;
      if (X[i] + Y[i] < BLK) {
        if (s + X[i] - 1 < d) {
          c[d][s]++;
          c[d][s+X[i]]--;
        }
        else {
          c[d][s]++;
          c[d][0]++;
          c[d][s+X[i]-d]--;
        }
      }
      else {
        for (int j = s; j < M; j += d) {
          pfx[j]++;
          if (j + X[i] < M) pfx[j+X[i]]--;
        }
      }
    }
  }
  FOR(d, 1, BLK) {
    FOR(j, 1, BLK) {
      c[d][j] += c[d][j-1];
    }
  }
  FOR(i, 1, M) pfx[i] += pfx[i-1];
  FOR(i, 1, N+1) cur[i] = on[i];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  FOR(i, 1, N+1) {
    cin >> X[i] >> Y[i];
  }
  memset(on, -1, sizeof on);
  memset(cur, -1, sizeof cur);

  F0R(t, M) {
    if (t % BLK == 0) {
      rebuild();
    }

    int op, k; cin >> op >> k;
    if (op == 1) {
      total++;
      on[k] = t;
      if (cur[k] >= 0) {
        T.erase({cur[k], k});
      }
      else {
        S.insert({on[k], k});
      }
    }
    else {
      total--;
      if (cur[k] >= 0) {
        T.insert({cur[k], k});
      }
      else {
        S.erase({on[k], k});
      }
      on[k] = -1;
    }

    // FOR(j, 0, 10) {
    //   cout << pfx[j] << ' ';
    // }
    // cout << endl;
    int ans = pfx[t];
    FOR(i, 1, BLK) {
      ans += c[i][t%i];
    }
    for (auto [s, i]: S) {
      if (inMaintenance(i, s, t)) ans++;
    }
    for (auto [s, i]: T) {
      if (inMaintenance(i, s, t)) ans--;
    }
    cout << total-ans << '\n';
  }
}
