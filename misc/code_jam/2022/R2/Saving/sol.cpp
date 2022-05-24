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

const int maxn = 10;
int N;
array<ll, 2> a[maxn], candies[maxn+1];

ll dist(array<ll, 2> a, array<ll, 2> b) {
  return (a[0]-b[0])*(a[0]-b[0]) + 
         (a[1]-b[1])*(a[1]-b[1]);
}

vector<int> closest(int i, int m2) {
  pair<ll, vector<int>> ret = {dist(a[i], candies[0]), {-1}};
  F0R(j, N) if (!(m2 & (1<<j))) {
    ll d = dist(a[i], candies[j+1]);
    if (d < ret.first) {
      ret = {d, {j}};
    }
    else if (d == ret.first) {
      ret.second.push_back(j);
    }
  }
  vector<int> r;
  for (auto x: ret.second) {
    if (x != -1) r.push_back(x);
  }
  return r;
}

pair<int,int> dp[1<<maxn][1<<maxn];
void f(int m1, int m2) {
  if (dp[m1][m2] != make_pair(-1, -1)) return;
  if (m1 == (1 << N) - 1) return;
  F0R(i, N) {
    if (!(m1 & (1<<i))) {
      auto v = closest(i, m2);
      /*
      if (m1 == 0 && m2 == 0 && i == 2) {
        cout << a[i] << endl;
        cout << candies[v[0]+1] << endl;
        cout << v << endl;
      }
      */
      for (int j: v) {
        f(m1 | (1<<i), m2 | (1<<j));
        dp[m1 | (1<<i)][m2 | (1<<j)] = {m1, m2};
      }
    }
  }
}

int get_log(int x) {
  int r = 0;
  while ((x >> 1) > 0) {
    x >>= 1;
    r++;
  }
  return r;
}

void solve() {
  cin >> N;
  F0R(i, 1<<maxn) {
    F0R(j, 1<<maxn) {
      dp[i][j] = {-1, -1};
    }
  }
  F0R(i, N) {
    cin >> a[i][0] >> a[i][1];
  }
  F0R(i, N+1) {
    cin >> candies[i][0] >> candies[i][1];
  }
  f(0, 0);

  if (dp[(1<<N)-1][(1<<N)-1].first != -1) {
    vector<pair<int,int>> v;
    int m1 = (1<<N)-1;
    int m2 = (1<<N)-1;
    while (m1 != 0) {
      auto [nm1, nm2] = dp[m1][m2];
      int x = get_log(m1 ^ nm1);
      int y = get_log(m2 ^ nm2);

      m1 = nm1;
      m2 = nm2;
      v.push_back({x+1, y+2});
    }

    reverse(all(v));
    cout << "POSSIBLE\n";
    for (auto [x, y]: v) {
      cout << x << ' ' << y << '\n';
    }
  }
  else {
    cout << "IMPOSSIBLE\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  FOR(tt, 1, T+1) {
    cout << "Case #" << tt << ": ";
    solve();
  }
}
