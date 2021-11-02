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

const int M = 1e9+7;
void madd(int& a, int b) {
  a += b;
  if (a > M) a -= M;
}
int mult(int a, int b) {
  return (1LL*a*b) % M;
}
int msub(int a, int b) {
  madd(a, M-b);
  return a;
}

const int maxn = 1e6+6;
string s;

int solve() {
  int n; cin >> n;
  cin >> s;
  bool allf = true;
  for (char c: s) if (c != 'F') allf = false;
  if (allf) return 0;

  vector<int> changes(n);
  char last = '#';
  int change = 0;
  int sum = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] != 'F') {
      if (last != '#' && last != s[i]) change++;
      last = s[i];
    }
    madd(sum, change);
    changes[i] = change;
  }

  int extraf = 0;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] != 'F') {
      madd(ans, mult(1+extraf, msub(sum, mult(n-i,changes[i]))));
      extraf = 0;
    }
    else extraf++;

    sum = msub(sum, changes[i]);
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
