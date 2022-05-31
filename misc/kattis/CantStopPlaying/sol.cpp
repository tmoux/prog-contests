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
int A[maxn];

using state = array<int, 3>;

bool valid(state s) {
  return s[0] != -1;
}

int lsb(int x) {
  return x & (-x);
}

map<state, map<pair<int, int>, state>> trans;
state getTrans(state m, int d, int l) { // returns next state or -1 if invalid transition
  if (trans[m].count({d, l})) return trans[m][{d, l}];  
  auto [mx, mask1, mask2] = m;
  auto& res = trans[m][{d, l}];
  if (l == 0) {
    if (mask1 == 0) {
      if (d < mx) {
        return res = {mx, 1<<d, mask2};
      }
      else if (d == mx) {
        return res = {mx+1, 0, mask2};
      }
      else {
        return res = {d, 0, mask2 | (1<<mx)};
      }
    }
    else if ((1<<d) <= lsb(mask1)) {
      int nmask1 = mask1 + (1<<d);
      if (nmask1 < (1<<mx)) {
        return res = {mx, nmask1, mask2};
      }
      else {
        return res = {mx+1, 0, mask2};
      }
    }
    else return res = {-1, -1, -1};
  }
  else {
    if (mask2 == 0) {
      if (d < mx) {
        return res = {mx, mask1, 1<<d};
      }
      else if (d == mx) {
        return res = {mx+1, mask1, 0};
      }
      else {
        return res = {d, mask1 | (1<<mx), 0};
      }
    }
    else if ((1<<d) <= lsb(mask2)) {
      int nmask2 = mask2 + (1<<d);
      if (nmask2 < (1<<mx)) {
        return res = {mx, mask1, nmask2};
      }
      else {
        return res = {mx+1, mask1, 0};
      }
    }
    else return res = {-1, -1, -1};
  }
}

int CNT = 0;

map<state, state> dp[maxn];
state f(int i, state m) {
  CNT++;
  if (i == N) {
    auto [mx, mask1, mask2] = m;
    if (mask1 == 0 && mask2 == 0) {
      return m;
    }
    else return {-1, -1, -1};
  }
  else {
    if (dp[i].count(m)) return dp[i][m];
    state& res = dp[i][m];
    res = {-1, -1, -1};
    state mL = getTrans(m, A[i], 0);
    state mR = getTrans(m, A[i], 1);
    if (valid(mL) && valid(f(i+1, mL))) {
      return res = mL;
    }
    else if (valid(mR) && valid(f(i+1, mR))) {
      return res = mR;
    }
    else return res;
  }
}

void recon(int i, state m, string& ret) {
  if (i == N) return;
  assert(dp[i].count(m) && valid(dp[i][m]));
  state mL = getTrans(m, A[i], 0);
  state mR = getTrans(m, A[i], 1);
  if (dp[i][m] == mL) {
    ret += 'l';
    recon(i+1, mL, ret);
  }
  else if (dp[i][m] == mR) {
    ret += 'r';
    recon(i+1, mR, ret);
  }
  else assert(false);
}

int maxcnt = 0;

void solve() {
  CNT = 0;
  auto lg = [&](int x) {
    int r = -1;
    while (x > 0) {
      r++;
      x >>= 1;
    }
    return r;
  };

  cin >> N;
  F0R(i, N) {
    dp[i].clear();
  }
  F0R(i, N) {
    cin >> A[i];
    A[i] = lg(A[i]);
  }

  state ans = f(1, {A[0], 0, 0});
  if (valid(ans)) {
    string ret; ret += 'l';
    recon(1, {A[0], 0, 0}, ret);
    cout << ret << '\n';
  }
  else {
    cout << "no\n";
  }
  ckmax(maxcnt, CNT);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
  DEBUG(maxcnt);
}
