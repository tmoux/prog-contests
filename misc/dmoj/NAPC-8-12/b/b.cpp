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

int len(int n) {
  int res = 0;
  for (int i = 1; i <= n; i++) {
    if (i < 10) res++;
    else res += 2;
  }
  return res;
}

string s;

vector<int> ans;
bool Left[100];

void search(int i) {
  if (i == s.size()) {
    for (int i: ans) {
      cout << i << ' ';
    }
    cout << '\n';
    exit(0);
  }
  else {
    //try 1
    int d1 = s[i]-'0';
    if (Left[d1]) {
      Left[d1] = false;
      ans.push_back(d1);

      search(i+1);

      ans.pop_back();
      Left[d1] = true;
    }

    if (i+1 < s.size()) {
      int d2 = (s[i]-'0') * 10 + (s[i+1]-'0');
      if (Left[d2]) {
        Left[d2] = false;
        ans.push_back(d2);

        search(i+2);

        ans.pop_back();
        Left[d2] = true;
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> s;
  int n;
  for (int i = 1; i <= 50; i++) {
    if (len(i) == s.size()) {
      n = i;
      break;
    }
  }
  for (int i = 1; i <= n; i++) Left[i] = true;
  search(0);
}
