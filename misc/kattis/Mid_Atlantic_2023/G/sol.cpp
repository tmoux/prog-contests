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

const int maxn = 1005;
int N;

ll X[maxn], Y[maxn];

ll sqr(ll x) {
  return x * x;
}
ll dist(int i, int j) {
  return sqr(X[i] - X[j]) + sqr(Y[i] - Y[j]);
}
ll d[maxn][maxn];

using vi = vector<int>;
using pii = pair<int, int>;
vi num;
vector<pii> st;
vector<vector<pii>> ed;
int Time;
template<class F>
int dfs(int at, int par, F& f) {
  int me = num[at] = ++Time, e, y, top = me;
  for (auto pa : ed[at]) if (pa.second != par) {
      tie(y, e) = pa;
      if (num[y]) {
        top = min(top, num[y]);
        if (num[y] < me)
          st.emplace_back(at, y);
      } else {
        int si = sz(st);
        int up = dfs(y, e, f);
        top = min(top, up);
        if (up == me) {
          st.emplace_back(at, y);
          f(vector<pii>(st.begin() + si, st.end()));
          st.resize(si);
        }
        else if (up < me) st.emplace_back(at, y);
        else { /* e is a bridge */ }
      }
    }
  return top;
}

template<class F>
void bicomps(F f) {
	num.assign(sz(ed), 0);
	FOR(i,0,sz(ed)) if (!num[i]) dfs(i, -1, f);
}

bool check(ll x) {
  ed = vector<vector<pii>>(N+1);
  F0R(i, N+1) {
    F0R(j, N+1) {
      if (i == j) continue;
      if (d[i][j] <= x) ed[i].emplace_back(j, i * (N + 1) + j);
    }
  }
  vector<bool> V(N+1, false);
  bicomps([&](const vector<pii>& edges) {
    bool has0 = false;
    for (auto [a, b]: edges) {
      has0 |= a == 0 || b == 0;
    }
    if (has0) {
      for (auto [a, b]: edges) {
        if (a > 0) V[a] = 1;
        if (b > 0) V[b] = 1;
      }
    }
  });

  return std::count(all(V), true) == N;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cout << fixed << setprecision(10);
  cin >> N;
  FOR(i, 1, N+1) {
    cin >> X[i] >> Y[i];
  }
  F0R(i, N+1) {
    F0R(j, N+1) {
      d[i][j] = dist(i, j);
    }
  }

  ll lo = 0, hi = std::numeric_limits<long long>::max();
  while (lo + 1 < hi) {
    ll mid = (lo + hi) / 2;
    (check(mid) ? hi : lo) = mid;
  }

  cout << sqrt(hi) << '\n';
}
