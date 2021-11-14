#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

// Template {{{
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

namespace std {
  template<class Fun>
  class y_combinator_result {
    Fun fun_;
  public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
   
    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
      return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
  };
   
  template<class Fun>
  decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
  }
} // namespace std
// }}}

bool brute(int N, int M, vector<int> B, vector<int> Z) {
  vector<int> fB;
  FOR(i, 1, sz(B)) {
    fB.push_back(B[i] - B[i-1]);
    if (fB.back() < 0) return false;
  }
  
  int i = 0;
  for (int x: fB) {
    //cerr << "trying to find " << x << endl;
    //check if there is a j s.t. sum(Z[i]..Z[j]) = x
    bool found = false;
    vector<bool> sum(x+1, false);
    vector<int> ones;
    while (i < M) {
      if (Z[i] > 0) {
        if (sz(ones) < 400) {
          sort(all(ones), greater<int>());
          vector<int> toadd;
          for (int j: ones) {
            if (j + Z[i] <= x && !sum[j+Z[i]]) {
              sum[j+Z[i]] = true;
              toadd.push_back(j+Z[i]);
            }
          }
          for (int j: toadd) ones.push_back(j);
        }
        else {
          for (int j = x; j >= 0; j--) {
            if (sum[j] && j + Z[i] <= x && !sum[j+Z[i]]) {
              sum[j+Z[i]] = true;
              ones.push_back(j+Z[i]);
            }
          }
        }
      }
      if (Z[i] <= x && !sum[Z[i]]) {
        sum[Z[i]] = true;
        ones.push_back(Z[i]);
      }
      i++;
      if (sum[x]) {
        found = true;
        break;
      }
    }

    if (!found) return false;
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    int N, M; cin >> N >> M;
    vector<int> B(N), Z(M);
    for (auto& i: B) cin >> i;
    for (auto& i: Z) cin >> i;
    cout << (brute(N, M, B, Z) ? "YES" : "NO") << '\n';
    //cout << (solve(N, M, B, Z) ? "YES" : "NO") << '\n';
  }
}
