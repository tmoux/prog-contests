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

void solve() {
  int N, Q; cin >> N >> Q;
  string a, b; 
  int x, y; 
  cin >> a >> x;
  if (N > 1) cin >> b >> y;
  auto calc = [&](string r) {
    int c1 = 0, c2 = 0;
    F0R(i,Q) {
      if (a[i] == r[i]) c1++;
      if (N > 1 && b[i] == r[i]) c2++;
    }
    return c1 == x && (N == 1 || c2 == y);
  };
  if (N == 1 || Q <= 4) {
    vector<string> v;
    for (int mask = 0; mask < (1<<Q); mask++) {
      string r = "";
      F0R(j,Q) {
        if (mask & (1<<j)) r += 'F';
        else r += 'T';
      }
      if (calc(r)) {
        v.push_back(r); 
      }
    }
    int D = v.size();
    int num = 0;
    string ans = "";
    for (int i = 0; i < Q; i++) {
      int t = 0, f = 0;
      for (int j = 0; j < D; j++) {
        if (v[j][i] == 'T') t++;
        else f++;
      }
      num += max(t,f);
      ans += t>f?'T':'F';
      //cout << max(t,f) << '\n';
    }
    //DEBUG(num);
    //DEBUG(D);
    /*
    cout << '\n';
    trav(i,v) {
      cout << i << '\n';
    }
    */
    int gc = __gcd(num,D);
    num /= gc;
    D /= gc;
    cout << ans << ' ' << num << '/' << D << '\n';
  }
  else {
    int mid = Q/2;
    vector<int> tcount(Q,0), fcount(Q,0);
    map<pi,pair<vi,vi>> mp;
    map<pi,int> cntMP;
    for (int mask = 0; mask < (1<<mid); mask++) {
      string r = "";
      int ca = 0, cb = 0;
      F0R(j,mid) {
        if (mask & (1<<j)) r += 'F';
        else r += 'T';

        if (r[j] == a[j]) ca++;
        if (r[j] == b[j]) cb++;
      }
      if (!mp.count(make_pair(ca,cb)))
        mp[make_pair(ca,cb)] = {vector<int>(Q,0),vector<int>(Q,0)};
      F0R(j,mid) {
        if (r[j] == 'T')
          mp[make_pair(ca,cb)].f[j]++;
        else
          mp[make_pair(ca,cb)].s[j]++;
      }
      cntMP[make_pair(ca,cb)]++;
    }
    for (int mask = 0; mask < (1<<(Q-mid)); mask++) {
      string r = "";
      int ca = 0, cb = 0;
      F0R(j,(Q-mid)) {
        if (mask & (1<<j)) r += 'F';
        else r += 'T';

        if (r[j] == a[mid+j]) ca++;
        if (r[j] == b[mid+j]) cb++;
      }
      if (mp.count(make_pair(x-ca,y-cb))) {
        auto& tc = mp[make_pair(x-ca,y-cb)].f;
        auto& fc = mp[make_pair(x-ca,y-cb)].s;
        F0R(j,mid) {
          tcount[j] += tc[j];
          fcount[j] += fc[j];
        }
        int add = cntMP[make_pair(x-ca,y-cb)];
        F0R(j,(Q-mid)) {
          if (r[j] == 'T') tcount[j+mid] += add;
          else fcount[j+mid] += add;
        }
      }
    }
    int D = tcount[0] + fcount[0];
    int num = 0;
    string ans = "";
    F0R(j,Q) {
      if (tcount[j] > fcount[j]) {
        ans += 'T';
      }
      else {
        ans += 'F';
      }
      num += max(tcount[j],fcount[j]);
      //cout << j << ": " << max(tcount[j],fcount[j]) << '\n';
      //cout << j << ": " << (tcount[j]+fcount[j]) << '\n';
    }
    int gc = __gcd(num,D);
    num /= gc;
    D /= gc;
    cout << ans << ' ' << num << '/' << D << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": ";
    solve();
  }
}
