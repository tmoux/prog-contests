#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

namespace std {
  template<class Fun>
  class y_combinator_result {
    Fun fun_;
  public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
   
    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
      return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
  };
   
  template<class Fun>
  decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
  }
} // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
  return os << ']'; 
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  const int MX = 1 << 5;
  vector<bool> good(MX, 0);
  auto pack = [&](int a, int b, int c, int d, int m) -> int {
    return 2 * (2 * (2 * (2 * a + b) + c) + d) + m;
  };
  auto unpack = [&](int x) -> array<int, 5> {
    return {(x >> 4) & 1, (x >> 3) & 1, (x >> 2) & 1, (x >> 1) & 1, x & 1 };
  };
  F0R(a, 2) F0R(b, 2) F0R(m, 2) {
    int x = pack(a, b, a, b, m);
    good[x] = 1;
  }
  auto mask_is_good = [&](int mask) -> bool {
    F0R(i, MX) {
      if ((mask & (1 << i)) && !good[i]) return false;
    }
    return true;
  };

  auto trans = [&](int mask, int t) -> int {
    int ret = 0;
    F0R(i, MX) {
      if (mask & (1 << i)) {
        auto [a, b, c, d, m] = unpack(i);
        if (t == 0) a &= b;
        else if (t == 1) a |= b;
        else if (t == 2) b ^= a;
        else b ^= m;

        ret |= 1 << pack(a, b, c, d, m);
      }
    }
    return ret;
  };
  int T; cin >> T;

  int mx = 0;
  while (T--) {
    int A, B, C, D, M;
    cin >> A >> B >> C >> D >> M;
    // A = rng() % (1 << 10);
    // B = rng() % (1 << 10);
    // C = rng() % (1 << 10);
    // D = rng() % (1 << 10);
    // M = rng() % (1 << 10);

    int mask = 0;
    F0R(i, 30) {
      int a = (A >> i) & 1;
      int b = (B >> i) & 1;
      int c = (C >> i) & 1;
      int d = (D >> i) & 1;
      int m = (M >> i) & 1;

      int x = pack(a, b, c, d, m);
      // DEBUG(x);
      mask |= 1 << x;
    }
    map<int, int> dist;
    queue<int> q;
    q.push(mask);
    dist[mask] = 0;

    int ans = -1;

    auto update = [&](int x, int y) -> void {
      if (!dist.count(y)) {
        dist[y] = dist[x] + 1;
        q.push(y);
      }
    };
    while (!q.empty()) {
      int x = q.front(); q.pop();
      // cout << x << ": " << dist[x] << ' ' << good[x] << endl;
      if (mask_is_good(x)) {
        ans = dist[x];
        break;
      }
      if (dist.count(x))
      // auto [a, b, c, d, m] = unpack(x);
      F0R(i, 4) {
        update(x, trans(x, i));
        // cout << "trans " << x << ' ' << trans(x, i) << endl;
      }
    }
    cout << ans << '\n';
    ckmax(mx, ans);
  }

  // for (int a: {0, 1}) {
  //   for (int b: {0, 1}) {
  //     for (int m: {0, 1}) {
  //       cout << a << ' ' << b << ' ' << m << ":::::\n";
  //       map<pair<int, int>, int> dist;
  //       queue<pair<int, int>> q;
  //       q.push({a, b});
  //       dist[{a, b}] = 0;
  //       while (!q.empty()) {
  //         auto [x, y] = q.front(); q.pop();
  //         cout << "found " << x << ' ' << y << ' ' << dist[{x, y}] << endl;
  //         auto upd = [&](int nx, int ny) -> void {
  //           if (!dist.count({nx, ny})) {
  //             dist[{nx, ny}] = dist[{x, y}] + 1;
  //             q.push({nx, ny});
  //           }
  //         };
  //         upd(x & y, y);
  //         upd(x | y, y);
  //         upd(x, x ^ y);
  //         upd(x, y ^ m);
  //       }
  //     }
  //   }
  // }
}
