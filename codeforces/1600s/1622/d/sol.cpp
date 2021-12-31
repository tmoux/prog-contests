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
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
// }}}

const int M = 998244353;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
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

const int maxn = 5005;
int fac[maxn], ifac[maxn];

int choose(int n, int k) {
  if (n < 0 || k < 0) return 0;
  if (n < k) return 0;
  int ret = fac[n];
  ret = mult(ret, ifac[k]);
  ret = mult(ret, ifac[n-k]);
  return ret;
}

int n, k;
string s;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  fac[0] = ifac[0] = 1;
  for (int i = 1; i < maxn; i++) {
    fac[i] = mult(fac[i-1], i);
    ifac[i] = inverse(fac[i]);
  }
  cin >> n >> k;
  cin >> s;

  if (k == 0) {
    cout << 1 << '\n';
    return 0;
  }
  else {
    int total_ones = count(all(s), '1');

    int ans = 0;
    for (int i = 0; i < n; i++) {
      int cnt = s[i] == '1' ? 1 : 0;
      int j = i;
      while (j+1 < n && cnt + (s[j+1] == '1') <= k) {
        j++;
        if (s[j] == '1') cnt++;
      }
      if (total_ones >= k) {
        int x = j - i + 1;
        if (s[i] == '0') {
          madd(ans, choose(x-1, cnt-1));
          //cout << x-1 << ' ' << cnt-1 << ": " << choose(x-1, cnt-1) << endl;
        }
        else {
          madd(ans, choose(x-1, cnt));
          //cout << x-1 << ' ' << cnt << ": " << choose(x-1, cnt) << endl;
        }
      }
    }
    madd(ans, 1); //for original
    cout << ans << '\n';
  }

  /*
  set<string> vs;
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      int cnt = 0;
      for (int k = i; k <= j; k++) if (s[k] == '1') cnt++;
      if (cnt == 2) {
        for (int ii = i; ii <= j; ii++) {
          for (int jj = ii+1; jj <= j; jj++) {
            string ss = s;
            for (int k = i; k <= j; k++) {
              ss[k] = '0';
            }
            ss[ii] = ss[jj] = '1';
            vs.insert(ss);
          }
        }
      }
    }
  }
  cout << sz(vs) << endl;
  for (auto ss: vs) {
    cout << ss << '\n';
  }

  set<string> ms = {
    "0110110",
    "0011110",
    "0101110",

    "1010110",
    "1001110",
    "1011010",

    "1111000",
    "1110100",
    "1110010",
    "1110001",

    "1101100",
    "1101010",
    "1101001",

    "1100011",

    "1100110",
  };

  cout << sz(ms) << endl;
  for (string s: vs) {
    if (!ms.count(s)) {
      cout << s << endl;
    }
  }
  */
}
