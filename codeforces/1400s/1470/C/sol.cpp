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

int ask(int q) {
  cout << "? " << q+1 << endl;
  int res; cin >> res;
  return res;
}
void answer(int p) {
  cout << "! " << p+1 << endl;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, K; cin >> N >> K;

  int cur = N-1;
  assert(ask(cur) == K); // first one
  for (int i = 1; ; i++) {
    cur = (cur-(i-1)+N) % N;
    int k = ask(cur);
    if (k == K) continue;
    else if (k < K) {
      // binary search on right
      int lo = 0, hi = i + 1;
      while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        int nc = (cur + mid + N) % N;
        int kk = ask(nc);
        if (kk == K) {
          answer(nc);
          return 0;
        }
        else if (kk > K) {
          // gone too far
          hi = mid;
        }
        else lo = mid;
      }
      assert(false);
    }
    else if (k > K) {
      // binary search on left
      int lo = 0, hi = i + 1;
      while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        int nc = (cur - mid + N) % N;
        int kk = ask(nc);
        if (kk == K) {
          answer(nc);
          return 0;
        }
        else if (kk < K) {
          // gone too far
          hi = mid;
        }
        else lo = mid;
      }
      assert(false);
    }
  }

  // vector<int> v(N, K);
  // REP(1000) {
  //   // cout << v << endl;
  //   vector<int> nv(N, 0);
  //   for (int i = 0; i < N; i++) {
  //     if (i == 0) {
  //       nv[i+1] += v[i];
  //     }
  //     else {
  //       nv[(i-1+N)%N] += v[i]/2;
  //       nv[(i+1+N)%N] += v[i] - (v[i]/2);
  //     }
  //   }
  //   // if (v == nv) break;
  //   v = nv;
  // }
}
