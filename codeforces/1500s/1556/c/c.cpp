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

const int maxn = 1005;
int n;
ll c[maxn];

ll dp[maxn][maxn];


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> c[i];
  }

  ll ans = 0;
  for (int i = 1; i+1 <= n; i += 2) {
    ll take = min(c[i], c[i+1]);
    ans += take;
    ll extra = c[i] - take;
    ll midExtra = 0;

    if (c[i] >= c[i+1]) {
      for (int j = i+3; j <= n; j += 2) {
        ll left = c[j-1];
        ll right = c[j];
        if (right < left) {
          midExtra += left - right;
        }
        else {
          right -= left;
          if (right >= midExtra) {
            right -= midExtra;
            midExtra = 0;
            ll take = min(extra, right);
            ans += take + 1;
            right -= take;
            extra -= take;
            if (right > 0) break;
          }
          else {
            midExtra -= right;
          }
        }
      }
    }
  }
  cout << ans << '\n';
}
