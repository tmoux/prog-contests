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
int n;
int a[maxn];

void solve() {
  cin >> n;
  vector<vector<int>> ins(n+1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    ins[a[i]].push_back(i);
  }

  vector<int> ans(n+1);
  vector<int> needs, extras;
  for (int i = 1; i <= n; i++) {
    if (ins[i].empty()) {
      needs.push_back(i); 
    }
  }

  for (int i = 1; i <= n; i++) {
    ans[i] = a[i];
  }
  if (needs.size() == 1) {
    int need = needs[0];
    int needFiller = -1;
    for (int i = 1; i <= n; i++) {
      if (ins[i].size() > 1) {
        for (int j: ins[i]) {
          if (j != need) {
            ans[j] = need;
            needFiller = j;
            goto done;
          }
        }
      }
    }
    done:;
  }
  else {
    for (int i = 1; i <= n; i++) {
      if (ins[i].size() > 1) {
        ans[ins[i][0]] = i;
        for (int j = 1; j < ins[i].size(); j++) {
          extras.push_back(ins[i][j]);
        }
      }
    }
    assert(needs.size() == extras.size());

    auto is_derangement = [](vector<int>& a, vector<int>& b) {
      for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i]) return false;
      }
      return true;
    };

    while (!is_derangement(needs, extras)) {
      shuffle(all(needs), rng);
    }

    for (int i = 0; i < needs.size(); i++) {
      ans[extras[i]] = needs[i];
    }
  }
  
  int res = 0;
  for (int i = 1; i <= n; i++) if (a[i] == ans[i]) res++;
  cout << res << '\n';
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}
