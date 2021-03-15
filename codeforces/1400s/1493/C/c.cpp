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
#define mp make_pair
#define pb push_back
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

void solve() {
  int n, k; cin >> n >> k;
  string s; cin >> s;
  if (n % k != 0) {
    cout << -1 << '\n';
    return;
  }
  vector<int> cnt(26,0);
  F0R(i,n) {
    cnt[s[i]-'a']++;
  }
  bool flag = true;
  F0R(i,26) {
    if (cnt[i] % k != 0) flag = false;
  }
  if (flag) {
    cout << s << '\n';
    return;
  }
  F0Rd(i,n) {
    int c = s[i]-'a';
    cnt[c]--;
    int need = 0;
    vector<int> to_add(26,0);
    F0R(j,26) {
      if (cnt[j] % k != 0) {
        need += k-(cnt[j]%k);
        to_add[j] += k-(cnt[j]%k);
      }
    }
    /*
    cout << i << ": need = " << need << '\n';
    F0R(i,26) {
      cout << i << ": " << cnt[i] << '\n';
    }
    */
    int have = n-i;
    if (have >= need) {
      int start = -1;
      int left = have-need;
      assert(left % k == 0);
      FOR(j,c+1,26) {
        if (to_add[j] > 0) start = j;
        else if (left >= k) {
          to_add[c+1] += k;
          left -= k;
          start = j;
        }
        if (start != -1) break;
      }
      to_add[0] += left;
      if (start != -1) {
        //found answer
        cout << s.substr(0,i);
        cout << (char)(start+'a');
        to_add[start]--;
        F0R(i,26) while (to_add[i] > 0) {
          cout << (char)(i+'a');
          to_add[i]--;
        }
        cout << '\n';
        return;
      }
    }
  }
  assert(false);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) solve();
}
