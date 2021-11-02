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

const int maxx = 1e6+6;
bool isComposite[maxx];

int string_to_int(const string& s) {
    int res = 0;
    int mult = 1;
    for (int i = s.size()-1; i >= 0; i--) {
        res += (s[i]-'0') * mult;
        mult *= 10;
    }
    return res;
}

string ans;

void get_sub(const string& n, const string& cur, int i, int j) {
    if (!ans.empty()) return;
    if (cur.size() == j) {
        int x = string_to_int(cur);
        if (isComposite[x]) {
            ans = cur;
            return;
        }
    }
    else if (i < n.size()) {
        get_sub(n, cur+n[i], i+1, j);
        get_sub(n, cur, i+1, j);
    }
}

void solve() {
    ans.clear();
    int k; cin >> k;
    string n; cin >> n;

    for (int j = 1; ; j++) {
        //cout << "trying " << n << ' ' << j << endl;
        get_sub(n, "", 0, j);
        if (!ans.empty()) {
            cout << j << '\n';
            cout << ans << '\n';
            return;
        }
    }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(nullptr);
  isComposite[1] = true;
  for (int i = 2; i < maxx; i++) {
      if (!isComposite[i]) {
          for (int j = 2*i; j < maxx; j += i) {
              isComposite[j] = true;
          }
      }
  }
  int T; cin >> T;
  while (T--) solve();
}
