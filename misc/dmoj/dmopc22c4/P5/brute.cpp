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
int G[maxn];

int mex(vector<int> v) {
 sort(all(v)); v.erase(unique(all(v)), v.end());
 F0R(i, sz(v)) if (v[i] != i) return i;
 return sz(v);
}

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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  FOR(i, 1, N+1) {
    map<int, int> mp;
    int x = i;
    for (int j = 2; j*j <= i; j++) {
      if (x % j == 0) {
        while (x % j == 0) {
          x /= j;
          mp[j]++;
        }
      }
    }
    vector<int> v;
    for (int j = 2; j*j <= i; j++) {
      if (i % j == 0 && __gcd(j, i/j) > 1) {
        v.push_back(G[j] ^ G[i/j]);
      }
    }
    G[i] = mex(v);
    cout << i << ": " << G[i] << endl;
    continue;
    // if (G[i]) {
    //   cout << i << endl;
    // }
    if (G[i] == 5) {
      cout << i << ": " << G[i] << '\n';
      vector<int> vp;
      for (auto [_, c]: mp) {
        if (c > 1) vp.push_back(c);
      }
      sort(all(vp), greater());
      cout << vp << endl;
    }


    // check
    // bool hasE = 0;
    // int maxE = 0;
    // bool hasOne = 0;
    // for (auto [p, c]: mp) {
    //   if (c % 2 == 0) hasE = true;
    //   if (c == 1) hasOne = true;
    //   ckmax(maxE, c);
    // }
    // if (!hasE) {
    //   assert(G[i] == 0);
    // }
    // else if (hasOne) {
    //   assert(G[i] == 1);
    // }
    // else if (sz(mp) == 1) {
    //   assert(G[i] == 1);
    // }
    // else {
    //   assert(G[i] == maxE);
    // }
  }

  // for (int i = 1; i <= N; i *= 2) {
  //   cout << i << ": " << G[i] << endl;
  // }
}
