#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
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

const int maxn = 2e6+6;
namespace HH {
  const int base = rng() % 500 + 29;
  const int M1 = 1e9+9;
  const int M2 = 1e9+21;
  ll inverse1[maxn], inverse2[maxn];
  ll pow1[maxn], pow2[maxn];
  int ctoi(char c) {return c-'a'+1;}

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
    ll *prefix1, *prefix2;
    Hash(const vector<int>& s) {
      len = s.size();
      str = s;
      prefix1 = new ll[maxn];
      prefix2 = new ll[maxn];
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

    pair<ll, ll> shift(pair<ll, ll> p, int d) {
      return {(p.first * pow1[d]) % M1, (p.second * pow2[d]) % M2};
    };

    pair<ll, ll> add(pair<ll, ll> a, pair<ll, ll> b) {
      return {(a.first + b.first) % M1, (a.second + b.second) % M2};
    }

    ~Hash() {
      delete[] prefix1;
      delete[] prefix2;
    }
  };

  void init_inverse() {
    pow1[0] = 1;
    for (int i = 1; i < maxn; i++) {
      pow1[i] = (pow1[i-1] * base) % M1;
    }
    pow2[0] = 1;
    for (int i = 1; i < maxn; i++) {
      pow2[i] = (pow2[i-1] * base) % M2;
    }
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

int get_index(vector<int> A, vector<int> B) {

}

int solve() {
  int N; cin >> N;
  vector<int> A(N); for (auto& x: A) cin >> x;
  vector<int> B(N); for (auto& x: B) cin >> x;

  int i1 = get_index(A, B);
  if (i1 != -1) return i1;
  else {
    int i2 = get_index(B, A);
    return i2;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_inverse();

  int T; cin >> T;
  FOR(tc, 1, T+1) {
    cout << "Case #" << tc << ": " << solve() << '\n';
  }
}
