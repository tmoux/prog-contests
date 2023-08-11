#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;
 
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;
 
typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;
 
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a,x) for (auto& a : x)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
 
#define sz(x) (int)(x).size()
#define f first
#define s second
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename T>
ostream& operator<<(ostream& o, const vector<T>& v) {
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}

const int maxn = 2e5+5;
int n, m;
string s;
string b[6];
int pre_diff[6][maxn]; //prefix sum of # of characters that are different from s

int diff_in_range(int i, int l, int r) {
  return pre_diff[i][r] - (l == 0 ? 0 : pre_diff[i][l-1]);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> m;
  cin >> s;
  vector<char> abc = {'a','b','c'};
  {
    int i = 0;
    do {
      b[i].resize(n);
      for (int j = 0; j < n; j++) {
        b[i][j] = abc[j%3];
        pre_diff[i][j] = (b[i][j] != s[j]) + (j == 0 ? 0 : pre_diff[i][j-1]);
      }
      i++;
    } while (next_permutation(all(abc)));
  }

  while (m--) {
    int l, r; cin >> l >> r;
    l--; r--;
    int ans = n;
    for (int i = 0; i < 6; i++) {
      ckmin(ans, diff_in_range(i, l, r)); 
    }
    cout << ans << '\n';
  }
}
