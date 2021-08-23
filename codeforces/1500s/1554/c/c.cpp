#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;
 
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

int calc(const vector<int>& n, const vector<int>& m, int i, int x) {
  if (i < 0) return -1;
  if (n[i] == 0 && m[i] == 0) {
    int c = calc(n, m, i-1, x);
    if (c != -1) return c;
    else return x|(1<<i);
  }
  else if (n[i] == 0 && m[i] == 1) {
    return calc(n, m, i-1, x|(1<<i));
  }
  else if (n[i] == 1 && m[i] == 0) {
    return x;
  }
  else if (n[i] == 1 && m[i] == 1) {
    return calc(n, m, i-1, x);
  }
  else assert(false);
}

void solve() {
  int n, m; cin >> n >> m;
  vector<int> vn(30), vm(30);
  for (int i = 0; i <= 29; i++) vn[i] = (n>>i)&1;
  for (int i = 0; i <= 29; i++) vm[i] = (m>>i)&1;
  //DEBUG(vn);
  //DEBUG(vm);
  cout << calc(vn, vm, 29, 0) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
