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

int c1, t1 = 0;
int c2, t2 = 0;

int solve() {
  vector<vector<bool>> data(100,vector<bool>(10000));
  for (int i = 0; i < 100; i++) {
    string s; cin >> s;
    for (int j = 0; j < 10000; j++) {
      data[i][j] = s[j] == '1';
    }
  }
  vector<pair<double,int>> v;
  for (int i = 0; i < 100; i++) {
    int cnt = accumulate(all(data[i]),0);
    v.push_back({(double)cnt/10000,i});
  }
  //get hardest problems
  vector<pair<double,int>> problems;
  for (int j = 0; j < 10000; j++) {
    int cnt = 0;
    for (int i = 0; i < 100; i++) {
      cnt += data[i][j];
    }
    problems.push_back({(double)cnt/100,j});
  }
  sort(all(problems));
  map<int,int> skilled;
  int K = 10000/6;
  for (int i = 0; i < K; i++) {
    //cout << problems[i].second << ": " << problems[i].first << '\n';
    for (int j = 0; j < 100; j++) {
      if (data[j][problems[i].second]) skilled[j]++;
    }
  }
  vector<pair<int,int>> skilledV;
  for (auto p: skilled) skilledV.push_back({p.second,p.first});
  sort(all(skilledV)); reverse(all(skilledV));
  /*
  for (auto p: skilledV) {
    cout << p.second << ": " << p.first << '\n';
  }
  */
  /*
  sort(all(v)); reverse(all(v));
  for (auto p: v) {
    cout << p.second << ": " << p.first << '\n';
  }
  */
  //Try this: return player who did best on the hardest K questions.
  int diff = 80;
  if (skilledV[0].first-skilledV[1].first > diff) {
    t1++;
    if (skilledV[0].second+1 == 1) c1++;
    return skilledV[0].second+1;
  }
  else {
    vector<int> highs;
    for (auto p: skilledV) if (p.first > K/2-70) {
      highs.push_back(p.second);
    }
    map<int,int> mids;
    for (int i = 10000/2-10000/6; i < 10000/2; i++) {
      for (int j: highs) {
        if (data[j][problems[i].second]) mids[j]++;
      }
    }
    pair<int,int> mn = {1e9,-1};
    for (auto p: mids) {
      ckmin(mn,{p.second,p.first});
    }
    t2++;
    if (mn.second+1 == 1) c2++;
    return mn.second+1;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  int P; cin >> P;
  for (int tc = 1; tc <= T; tc++) {
    int ans = solve();
    cout << "Case #" << tc << ": " << ans << '\n';
  }
  /*
  cout << c1 << " / " << t1 << ": " << (double)c1/t1 << '\n';
  cout << c2 << " / " << t2 << ": " << (double)c2/t2 << '\n';
  cout << "total " << (double)(c1+c2)/(t1+t2) << '\n';
  */
}
