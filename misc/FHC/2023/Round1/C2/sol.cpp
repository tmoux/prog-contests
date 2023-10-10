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

namespace Mobius {
  const int maxn = 4e6+6;
  int mu[maxn];

  void mobius_sieve() {
    mu[1] = 1;
    for (int i = 1; i < maxn; i++) {
      for (int j = 2*i; j < maxn; j += i) {
        mu[j] -= mu[i];
      }
    }
  }
}
using namespace Mobius;

vector<int> divs[maxn];

ll solve() {
  int N; cin >> N;
  string s; cin >> s;
  vector<int> on(N+1, 0);
  for (int i = 1; i <= N; i++) on[i] = s[i-1] - '0';

  vector<int> Flip(N+1, 0);
  int cur_ans = 0;
  for (int i = 1; i <= N; i++) {
    // for (int d: divs[i]) {
    //   if (mu[d] != 0) {
    //     Flip[i] ^= on[i / d];
    //   }
    // }
    Flip[i] = on[i];
    if (Flip[i]) {
      cur_ans++;
      for (int j = i; j <= N; j += i) on[j] ^= 1;
    }
  }

  int Q; cin >> Q;
  ll ans = 0;
  REP(Q) {
    int b; cin >> b;
    if (Flip[b]) {
      cur_ans--;
    }
    else cur_ans++;
    Flip[b] ^= 1;

    ans += cur_ans;

    // for (int j = b; j <= N; j += b) {
    //   on[j] ^= 1;
    // }

    // int cnt = 0;
    // for (int i = 1; i <= N; i++) {
    //   int x = 0;
    //   for (int d: divs[i]) {
    //     if (mu[d] != 0) {
    //       x ^= on[i / d];
    //     }
    //   }
    //   cnt += x;
    // }
    // ans += cnt;
    // cout << "rep " << cur_ans << endl;
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  // mobius_sieve();
  // for (int i = 1; i < maxn; i++) {
  //   for (int j = 1; i*j < maxn; j++) {
  //     divs[i*j].push_back(i);
  //   }
  // }
  int T; cin >> T;
  FOR(tc, 1, T+1) {
    cout << "Case #" << tc << ": " << solve() << '\n';
  }

  // int N; cin >> N;
  // vector<map<int, int>> V(N+1);

  // map<int, int> MP;
  // for (int i = 1; i <= N; i++) {
  //   V[i][i]++;
  //   for (int d = 1; d < i; d++) {
  //     if (i % d == 0) {
  //       for (auto [x, c]: V[d]) {
  //         V[i][x] += c;
  //       }
  //     }
  //   }
  //   cout << i << ": " << V[i] << endl;
  //   for (auto [x, c]: V[i]) {
  //     int y = i / x;
  //     if (!MP.count(y)) MP[y] = c;
  //     else assert(MP[y] == c);
  //   }
  // }
  // for (int i = 1; i <= 20; i++) {
  //   cout << i << ": " << (MP[i] % 2) << endl;
  // }
}
