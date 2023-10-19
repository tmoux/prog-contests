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

/*
** Consider in reverse: we don't have any choices:
** If not increasing, must reverse it
** If still not increasing, impossible
** Else, reverse prefix sum operation.
** If n >= 3, the number of operations is <= 1.5 * 1e6, so just simulate it
** If n = 2, then (a, b) -->* (a, b % a) -> (b % a, a)
** This is like Euclidean algorithm, check if it terminates in the middle
 */

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<ll> A(N); for (auto& x: A) cin >> x;
  vector<ll> B(N); for (auto& x: B) cin >> x;
  if (N == 1) {
    if (A[0] == B[0]) {
      cout << "SMALL\n";
      cout << 0 << '\n';
    }
    else cout << "IMPOSSIBLE\n";
  }
  else {
    ll total_ops = 0;
    string ans;
    auto addp = [&](ll x) {
      total_ops += x;
      REP(x) {
        if (sz(ans) <= 200000) ans += 'P';
        else break;
      }
    };
    if (N == 2) {
      while (B != A) {
        if (B[0] == B[1]) break;
        else if (B[0] < B[1]) {
          if (A[0] == B[0] && A[1] <= B[1] && A[1] % A[0] == B[1] % A[0]) {
            ll take = (B[1] - A[1]) / A[0];
            B[1] -= A[0] * take;
            addp(take);
            break;
          }
          else if (A[1] == B[0] && A[0] <= B[1] && A[0] % A[1] == B[1] % A[1]) {
            ll take = (B[1] - A[0]) / A[1];
            B[1] -= A[1] * take;
            addp(take);
            ans += 'R';
            reverse(all(B));
            break;
          }
          else {
            ll x = B[1] % B[0] == 0 ? B[0] : B[1] % B[0];
            ll take = (B[1] - x) / B[0];
            B[1] -= B[0] * take;
            addp(take);
          }
        }
        else {
          ans += 'R';
          reverse(all(B));
        }
      }
    }
    else {
      while (B != A) {
        bool increasing = true;
        FOR(i, 1, N) {
          if (B[i] <= B[i-1]) increasing = false;
        }
        if (increasing) {
          for (int i = N-1; i > 0; i--) B[i] -= B[i-1];
          total_ops++;
          ans += 'P';
        }
        else if (!ans.empty() && ans.back() == 'R') break;
        else {
          reverse(all(B));
          ans += 'R';
        }
      }
    }
    // output
    if (A == B) {
      reverse(all(ans));
      if (sz(ans) <= 200000) {
        cout << "SMALL\n";
        cout << sz(ans) << '\n';
        cout << ans << '\n';
      }
      else {
        cout << "BIG\n";
        cout << total_ops << '\n';
      }
    }
    else cout << "IMPOSSIBLE\n";
  }
}
