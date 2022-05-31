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

const int maxn = 1005;
int N, M;
string S[maxn];

namespace HH {
  const int base = 29;
  const int M1 = 1e9+9;
  const int M2 = 1e9+21;
  ll inverse1[maxn], inverse2[maxn];
  int ctoi(char c) {return c-'A'+1;}

  ll modexp(ll x, ll n, int M) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2,M);
    return (x*modexp((x*x)%M,n/2,M))%M;
  }

  struct Hash
  {
    int len;
    string str;
    vector<ll> prefix1, prefix2;
    Hash() {}
    Hash(const string& s) {
      len = s.size();
      str = s;
      prefix1.resize(maxn, 0);
      prefix2.resize(maxn, 0);
      prefix1[0] = 0;
      prefix2[0] = 0;
      ll mult1 = 1;
      ll mult2 = 1;
      for (int i = 0; i < sz(s); i++) {
        prefix1[i+1] = (prefix1[i] + (ctoi(s[i])*mult1)%M1)%M1;  
        mult1 = (mult1*base)%M1;

        prefix2[i+1] = (prefix2[i] + (ctoi(s[i])*mult2)%M2)%M2;  
        mult2 = (mult2*base)%M2;
      }
    }

    pair<ll,ll> sub(int l, int r) { //returns hash of [l,r] inclusive, 1-indexed
      return {((prefix1[r]-prefix1[l-1]+M1)*inverse1[l-1])%M1,
        ((prefix2[r]-prefix2[l-1]+M2)*inverse2[l-1])%M2};
    }
  };

  void init_inverse() {
    inverse1[0] = 1;
    inverse1[1] = modexp(base,M1-2,M1);
    for (int i = 2; i < maxn; i++) {
      inverse1[i] = (inverse1[i-1] * inverse1[1]) % M1;
    }
    inverse2[0] = 1;
    inverse2[1] = modexp(base,M2-2,M2);
    for (int i = 2; i < maxn; i++) {
      inverse2[i] = (inverse2[i-1] * inverse2[1]) % M2;
    }   
  }
};
using namespace HH;

Hash hashes[maxn];

bool check(int K) {
  using pll = pair<ll,ll>;
  set<pll> t, s;
  for (int i = 1; i <= N; i++) {
    pll h = hashes[0].sub(i, min(N, i+K-1));
    t.insert(h);
  }

  FOR(j, 1, M) {
    for (int i = 1; i <= N; i++) {
      pll h = hashes[j].sub(i, min(N, i+K-1));
      if (t.count(h)) s.insert(h);
    }
  }

  int num = 0;
  for (int i = 1; i <= N; i++) {
    pll h = hashes[0].sub(i, min(N, i+K-1));
    if (!s.count(h)) num++;
  }
  return num * 2 >= N;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_inverse();
  cin >> N >> M;
  F0R(i, M) {
    cin >> S[i];
    hashes[i] = Hash(S[i]);
  }

  if (check(N)) {
    int lo = 0, hi = N;
    while (lo + 1 < hi) {
      int mid = (lo+hi)/2;
      if (check(mid)) {
        hi = mid;
      }
      else lo = mid;
    }
    cout << hi << '\n';
  }
  else {
    cout << -1 << '\n';
  }
}
