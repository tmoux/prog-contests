#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

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

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

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
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '['; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << ']'; }
// }}}

const int M = 1e9+7;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int msub(int a, int b) {
    madd(a, M-b);
    return a;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}

int n, m, rb, cb, rd, cd, p; 
struct State {
  int r, c, dx, dy;

  int to_int() {
    int base = 2 * (dx == -1 ? 0 : 1) + (dy == -1 ? 0 : 1);
    return (n * m * base) + (r * m + c);
  }

  void update_dir() {
    if (r + dx == n || r + dx == -1) dx *= -1;
    if (c + dy == m || c + dy == -1) dy *= -1;
  }

  void next() {
    r += dx;
    c += dy;
    update_dir();
  }
};

int solve() {
  cin >> n >> m >> rb >> cb >> rd >> cd >> p;
  rb--; cb--; rd--; cd--;

  p = mult(p, inverse(100));
  auto can_clean = [&](int r, int c) -> bool {
    return r == rd || c == cd;
  };

  vector<bool> vis(4*n*m, false);
  State cur = {rb, cb, 1, 1}; cur.update_dir();
  vector<int> lengths;
  int cycle_len = 0;
  int cur_cycle = 0;
  while (!vis[cur.to_int()]) {
    //cout << "at " << cur.r << ' '<< cur.c << endl;
    vis[cur.to_int()] = true;
    cycle_len++;
    if (can_clean(cur.r, cur.c)) {
      lengths.push_back(cur_cycle);
      cur_cycle = 1;
    }
    else cur_cycle++;
    cur.next();
  } 

  auto calc_expectation = [&](const vector<int>& lengths, int cycle_len) -> int {
    int a = 1;
    int num = 0;
    int acc = 0;
    for (int c: lengths) {
      acc += c;
      madd(num, mult(mult(p, a), acc));

      a = mult(a, msub(1, p));
    }
    //cout << num << ' ' << mult(201, inverse(256)) << endl;

    //cout << a << ' ' << mult(81, inverse(256)) << endl;

    madd(num, mult(cycle_len, a));

    int denom = msub(1, a);
    return mult(num, inverse(denom));
  };
  //cout << "cycle_len = " << cycle_len << endl;
  //cout << lengths << '\n';

  int E = calc_expectation(lengths, cycle_len);
  return E;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    cout << solve() << '\n';
  }
}
