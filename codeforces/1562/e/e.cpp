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

int solve() {
    int n; cin >> n;
    string s; cin >> s;

    vector<vector<int>> lcp(n+1, vector<int>(n+1, 0));
    for (int i = n-1; i >= 0; i--) {
        for (int j = n-1; j >= 0; j--) {
            lcp[i][j] = s[i] == s[j] ? 1 + lcp[i+1][j+1] : 0;
        }
    }

    auto comp = [&lcp, &s, &n](int i, int j) {
        assert(i < j);
        if (j + lcp[i][j] == n) return -1;
        else return s[i+lcp[i][j]] < s[j+lcp[i][j]] ? j+lcp[i][j] : -1;
    };

    int ans = 0;
    vector<int> lis(n);
    for (int i = 0; i < n; i++) {
        lis[i] = n-i;
        for (int j = 0; j < i; j++) {
            int k = comp(j, i);
            if (k != -1) {
                ckmax(lis[i], lis[j] + n-k);
            }
        }
        ckmax(ans, lis[i]);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int T; cin >> T;
    while (T--) cout << solve() << '\n';
}
