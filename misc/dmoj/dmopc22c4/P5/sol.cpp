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

const int maxn = 1e6+6;

int spf[maxn];

void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxn; i++) if (!spf[i]) {
      for (int j = i; j < maxn; j += i) {
        if (!spf[j]) spf[j] = i;
      }
    }
}

ll isSqr(ll x) {
  ll y = (ll)(sqrt(x));
  for (ll z = max(1LL, y-100); z <= y+100; z++) {
    if (z*z == x) return z;
  }
  return -1;
}

map<vector<int>, int> G;

int mex(vector<int> v) {
 sort(all(v)); v.erase(unique(all(v)), v.end());
 F0R(i, sz(v)) if (v[i] != i) return i;
 return sz(v);
}

vector<int> norm(vector<int> v) {
  vector<int> u;
  for (auto x: v) if (x > 1) u.push_back(x);
  sort(all(u));
  return u;
}

int F(vector<int> v) {
  v = norm(v);
  if (v.empty()) return 0;
  if (G.count(v)) return G[v];

  vector<int> moves;
  vector<int> C1(sz(v)), C2(sz(v));
  auto rec = y_combinator([&](auto rec, int i, bool ok) -> void {
    if (i == sz(v)) {
      if (ok) {
        moves.push_back(F(C1) ^ F(C2));
      }
    }
    else {
      for (int d = 0; d <= v[i]; d++) {
        C1[i] = d;
        C2[i] = v[i]-d;
        rec(i+1, ok || (C1[i] > 0 && C2[i] > 0));
      }
    }
  });
  rec(0, false);
  return G[v] = mex(moves);
}

int val(ll x) {
  vector<int> ps;
  ll o = x;
  for (ll i = 2; i*i*i <= o; i++) {
    if (x % i == 0) {
      int e = 0;
      while (x % i == 0) {
        x /= i;
        e++;
      }
      ps.push_back(e);
    }
  }
  ll y = isSqr(x);
  if (y != -1 && y > 1) {
    assert(y < maxn);
    ps.push_back(2);
  }
  return F(ps);
}


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  // for (int i = 1; i <= 200; i++) {
  //   cout << i << ": " << val(i) << endl;
  // }
  // cout << val(1000000000) << endl;
  int N; cin >> N;
  int s = 0;
  F0R(i, N) {
    ll x; cin >> x;
    s ^= val(x);
  }
  cout << (s ? "ALICE" : "BOB") << '\n';
  // int N; cin >> N;
  // FOR(i, 1, N+1) {
  //   vector<int> v;
  //   for (int j = 2; j*j <= i; j++) {
  //     if (i % j == 0 && __gcd(j, i/j) > 1) {
  //       v.push_back(G[j] ^ G[i/j]);
  //     }
  //   }
  //   G[i] = mex(v);
  //   if (G[i]) {
  //     cout << i << endl;
  //   }
  //   // cout << i << ": " << G[i] << '\n';
  // }

  // for (int i = 1; i <= N; i *= 2) {
  //   cout << i << ": " << G[i] << endl;
  // }
}
