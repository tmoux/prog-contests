#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a,x) for (auto& a : x)

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

void answer(int l1, int r1, int l2, int r2) {
    cout << l1+1 << ' ' << r1+1 << ' ' << l2+1 << ' ' << r2+1 << '\n';
}

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    int mid = n/2;
    for (int i = 0; i < mid; i++) {
        if (s[i] == '0') {
            answer(i, n-1, i+1, n-1);
            return;
        }
    }
    for (int i = mid; i < n; i++) {
        if (s[i] == '0') {
            answer(0, i, 0, i-1);
            return;
        }
    }
    if (n % 2 == 1) {
        answer(0, mid-1, mid+1, n-1);
    }
    else {
        answer(0, mid-1, mid, n-1);
    }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(nullptr);
  int T; cin >> T;
  while (T--) solve();
}
