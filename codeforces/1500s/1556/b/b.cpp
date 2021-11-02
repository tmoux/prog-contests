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

int solve() {
  int n; cin >> n;
  vector<int> a(n);
  F0R(i, n) {
    cin >> a[i];
    a[i] %= 2;
  }

  const ll INF = 1e18;
  auto calc = [&](const vector<int>& a, const vector<int>& b) {
    vector<int> za, zb;
    F0R(i, n) {
      if (a[i] == 0) za.push_back(i);
      if (b[i] == 0) zb.push_back(i);
    }
    if (za.size() != zb.size()) return INF;
    ll ans = 0;
    F0R(i, za.size()) {
      ans += abs(za[i] - zb[i]);
    }
    return ans;
  };
  
  ll ans = INF;

  vector<int> t1, t2;
  F0R(i, n) {
    t1.push_back(i % 2);
    t2.push_back((i+1) % 2);
  }

  ckmin(ans, calc(a, t1));
  ckmin(ans, calc(a, t2));

  if (ans < INF) return ans;
  else return -1;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
