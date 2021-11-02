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

vector<int> divisors(int x) {
  vector<int> ret;
  for (int i = 1; i*i <= x; i++) {
    if (x % i == 0) {
      ret.push_back(i);
      ret.push_back(x/i);
    }
  }
  return ret;
}

int solve() {
  int n; cin >> n;
  vector<int> a(n);
  map<int,int> mp;
  F0R(i, n) {
    cin >> a[i];
    mp[a[i]]++;
  }
  sort(all(a));
  for (auto p: mp) {
    if (p.second >= n/2) return -1;
  }

  //cout << a << endl;
  int ans = 0;
  FOR(i, 0, n) {
    FOR(j, i+1, n) {
      if (a[i] == a[j]) continue;
      int gc = a[j] - a[i];
      for (int d: divisors(gc)) {
        int cnt = 2;
        FOR(k, 0, i) {
          if ((a[i] - a[k]) % d == 0) cnt++;
        }
        FOR(k, j+1, n) {
          if ((a[k] - a[j]) % d == 0) cnt++;
        }
        if (cnt >= n/2) ckmax(ans, d);
      }
      //cout << gc << ' ' << a[i] << ' ' << a[j] << ": " << cnt << endl;
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    cout << solve() << '\n';
  }
}
