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

const int maxn = 1e6+6;
int spf[maxn];
vector<int> divisors[maxn];

void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxn; i++) if (!spf[i]) {
    for (int j = i; j < maxn; j += i) {
      if (!spf[j]) spf[j] = i;
    }
  }
  for (int i = 1; i < maxn; i++) {
    int x = i;
    while (x > 1) {
      divisors[i].push_back(spf[x]);
      x /= spf[x];
    }
  }
}

const int N = 30;
bitset<N> brute(int n, bitset<N> prev = bitset<N>()) {
  bitset<N> best;
  for (int mask = 0; mask < (1<<n); mask++) {
    map<int,int> cnt;
    bitset<N> tr;
    for (int i = 1; i <= n; i++) {
      if (mask & (1<<(i-1))) {
        tr[i-1] = 1;
      }
    }
    if ((prev & tr) == prev) {
      for (int i = 1; i <= n; i++) {
        if (mask & (1<<(i-1))) {
          for (int j = 1; j <= i; j++) {
            for (int d: divisors[j]) {
              cnt[d]++;
            }
          }
        }
      }
      bool poss = true;
      for (auto [_, c]: cnt) {
        if (c % 2 == 1) {
          poss = false;
          break;
        }
      }
      if (poss && tr.count() > best.count()) {
        best = tr;
      }
    }
  }
  cout << n << ": " << best.count() << '\n';
  for (int i = 1; i <= n; i++) {
    if (best[i-1]) {
      cout << i << ' ';
    }
  }
  cout << endl;
  return best;
}

void brute2(int n) {
  set<int> s;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  bitset<N> prev;
  for (int i = 1; i <= 21; i++) {
    prev = brute(i);
  }
}
