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

template<typename T>
void output_vector(const vector<T>& v) {
  for (auto it = v.begin(); it != v.end(); ++it) {
    cout << *it << (next(it) == v.end() ? '\n' : ' ');
  }
}

template<typename T>
void output_vector(const vector<T>& v, int offset) {
  for (auto it = v.begin(); it != v.end(); ++it) {
    cout << (*it + offset) << (next(it) == v.end() ? '\n' : ' ');
  }
}

int C = 0;
vector<int> solve() {
  int P; cin >> P;
  cerr << "on case " << ++C << endl;
  cerr << P << endl;
  int orig = P;
  vector<int> primes;
  for (int i = 2; i*i <= orig; i++) {
    while (P % i == 0) {
      P /= i;
      primes.push_back(i);
    }
  }
  if (P > 1) primes.push_back(P);
  ll sum = std::accumulate(all(primes), 0LL);
  const int SUM = 41;
  if (sum > SUM) {
    // cout << "FAILED AT " << orig << endl;
    // DEBUG(primes);
    return {};
  }
  else {
    cerr << primes << endl;
    vector<int> best = primes;
    REP(SUM - sum) best.push_back(1);

    vector<int> cur;
    ll cursum = 0;
    auto rec = y_combinator([&](auto rec, int i) -> void {
      if (sz(cur) > sz(best)) return;
      if (i == sz(primes)) {
        ll sum = std::accumulate(all(cur), 0LL);
        if (sum <= SUM) {
          if (sz(cur) + (SUM - sum) < sz(best)) {
            best = cur;
            REP(SUM - sum) best.push_back(1);
          }
        }
        return;
      }
      for (int j = 0; j < sz(cur); j++) {
        if (j > 0 && cur[j] == cur[j-1]) continue;
        int old = cur[j];
        cursum -= cur[j];
        cur[j] = old * primes[i];
        cursum += cur[j];
        if (cursum <= SUM) {
          rec(i+1);
        }
        cursum -= cur[j];
        cur[j] = old;
        cursum += cur[j];
      }

      cursum += primes[i];
      cur.push_back(primes[i]);
      if (cursum <= SUM) {
        rec(i+1);
      }
      cur.pop_back();
      cursum -= primes[i];
    });
    rec(0);

    assert(sz(best) <= 100);
    assert(std::accumulate(all(best), 0LL) == SUM);
    ll prod = 1;
    for (auto x: best) prod *= x;
    // DEBUG(orig);
    // DEBUG(best);
    assert(prod == orig);
    return best;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  FOR(tc, 1, T+1) {
    cout << "Case #" << tc << ": ";
    auto ans = solve();
    if (ans.empty()) {
      cout << -1 << '\n';
    }
    else {
      cout << sz(ans) << ' ';
      output_vector(ans);
    }
  }
}
