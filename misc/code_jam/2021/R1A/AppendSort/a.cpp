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

int solve() {
  int N; cin >> N;
  vector<vector<int>> v(N);
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    vector<int> d;
    while (x) {
      d.push_back(x%10);
      x /= 10;
    }
    reverse(all(d));
    v[i] = d;
  }
  auto is_less = [&](vector<int>& a, vector<int>& b) {
    if (a.size() < b.size()) return true;
    if (a.size() > b.size()) return false;
    for (int i = 0; i < a.size(); i++) {
      if (a[i] < b[i]) return true;
      else if (a[i] > b[i]) return false;
    }
    return false;
  };
  int ans = 0;
  auto can_make_bigger = [&is_less](int x, vector<int> a, vector<int> b) {
    while (a.size() < b.size()) {
      if (sz(b)-sz(a) <= x) a.push_back(9);
      else {
        int idx = a.size();
        a.push_back(b[idx]);
      }
    }
    return is_less(b,a);
  };
  auto add_nines = [&can_make_bigger,&is_less,&ans](vector<int>& a, vector<int>& b) {
    int x = b.size()+3;
    while (x-1 >= 0 && can_make_bigger(x-1,a,b)) {
      x--;
    }

    bool flag = true;
    for (int i = 0; i < a.size(); i++) {
      if (a[i] > b[i]) flag = false;
    }
    while (a.size() < b.size()) {
      ans++;
      if (flag) {
        if (sz(b)-sz(a) <= x) {
          if (flag) {
            int idx = a.size();
            int digit = b[idx] == 9 ? 9 : b[idx]+1;
            a.push_back(digit);
            if (a[idx] > b[idx]) flag = false;
          }
        }
        else {
          int idx = a.size();
          a.push_back(b[idx]);
        }
      }
      else a.push_back(0);
    }
    assert(is_less(b,a));
  };
  auto add_zeros = [&ans](vector<int>& a, vector<int>& b) {
    while (a.size() <= b.size()) {
      ans++;
      a.push_back(0);
    }
  };
  for (int i = 1; i < N; i++) {
    if (is_less(v[i-1],v[i])) continue;
    if (can_make_bigger(v[i-1].size()+3,v[i],v[i-1])) {
      add_nines(v[i],v[i-1]);
    }
    else {
      add_zeros(v[i],v[i-1]);
    }
    //cout << "i = " << v[i] << endl;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": " << solve() << '\n';
  }
}
