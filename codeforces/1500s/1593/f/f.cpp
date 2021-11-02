#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

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

/* requires c++20
template<typename T>
concept Container = requires(T a)
{
  { a.begin() } -> std::same_as<typename T::iterator>;
  { a.end() } -> std::same_as<typename T::iterator>;
};
*/

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<class T, template <class> class U>
ostream& operator<<(ostream& o, const U<T>& v) //requires Container<U<T>>
{
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}

const int maxn = 45;
int d[maxn];
bool dp[maxn][maxn][maxn][maxn]; //i, A length, A mod, B mod
int n, A, B;

struct Rec {
  int i, a_len, a_mod, b_mod;
};

Rec rec[maxn][maxn][maxn][maxn];

int exp10A[maxn], exp10B[maxn];

void recon(int i, int a_len, int a_mod, int b_mod, vector<char>& ans) {
  if (i == 0) {
    if (a_len == 1) ans.push_back('R');
    else ans.push_back('B');
    return;
  }
  auto [a, b, c, d] = rec[i][a_len][a_mod][b_mod];
  if (b < a_len) ans.push_back('R');
  else ans.push_back('B');
  recon(a, b, c, d, ans);
}

void solve() {
  cin >> n >> A >> B;
  string x; cin >> x;
  reverse(all(x));
  exp10A[0] = exp10B[0] = 1;
  F0R(i, n) {
    exp10A[i+1] = (exp10A[i] * 10) % A;
    exp10B[i+1] = (exp10B[i] * 10) % B;
  }
  F0R(i, n) {
    d[i] = x[i] - '0';
  }
  memset(dp, false, sizeof dp);
  memset(rec, 0, sizeof rec);

  //Base cases
  dp[0][1][d[0]%A][0] = true;
  dp[0][0][0][d[0]%B] = true;

  F0R(i, n-1) {
    for (int a_len = 0; a_len <= i+1; a_len++) {
      F0R(a_mod, A) {
        F0R(b_mod, B) {
          if (dp[i][a_len][a_mod][b_mod]) {
            int b_len = (i + 1) - a_len;
            //add to A
            int new_amod = (a_mod + exp10A[a_len] * d[i+1]) % A;
            dp[i+1][a_len+1][new_amod][b_mod] = true;
            rec[i+1][a_len+1][new_amod][b_mod] = {i, a_len, a_mod, b_mod};
            //add to B
            int new_bmod = (b_mod + exp10B[b_len] * d[i+1]) % B;
            dp[i+1][a_len][a_mod][new_bmod] = true;
            rec[i+1][a_len][a_mod][new_bmod] = {i, a_len, a_mod, b_mod};
          }
        }
      }
    }
  }

  int ans = n;
  vector<char> res;
  FOR(a_len, 1, n) {
    int b_len = n - a_len;
    if (abs(a_len - b_len) < ans && dp[n-1][a_len][0][0]) {
      ans = abs(a_len - b_len);
      vector<char> v;
      recon(n-1, a_len, 0, 0, v);
      res = v;
    }
  }

  if (ans == n) {
    cout << -1 << '\n';
  }
  else {
    for (char c: res) {
      cout << c;
    }
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}
