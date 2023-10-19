#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

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

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
  return os << ']'; 
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<int> z_function(vector<int> s) {
  int n = sz(s);
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r)
      z[i] = min (r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      ++z[i];
    if (i + z[i] - 1 > r)
      l = i, r = i + z[i] - 1;
  }
  return z;
}

int get_index(vector<int> A, vector<int> B) {
  int N = sz(A);
  auto AR = A; reverse(all(AR));
  auto BR = B; reverse(all(BR));
  vector<int> v;
  v = A; v.push_back(-1); for (auto x: AR) v.push_back(x);
  auto z_prefix_A = z_function(v);
  v = AR; v.push_back(-1); for (auto x: A) v.push_back(x);
  auto z_suffix_A = z_function(v);

  v = B; v.push_back(-1); for (auto x: BR) v.push_back(x);
  auto z_prefix_B = z_function(v);
  v = BR; v.push_back(-1); for (auto x: B) v.push_back(x);
  auto z_suffix_B = z_function(v);

  auto rev = [&](int i) {
    return N - 1 - i;
  };

  auto check_prefix_A = [&](int i) -> bool {
    if (i == 0) return true;
    assert(N - i >= i);
    return z_prefix_A[N+1 + rev(2*i - 1)] >= i;
  };
  auto check_suffix_A = [&](int i) -> bool {
    if (i == N) return true;
    assert(i >= N - i);
    return z_suffix_A[N+1 + (i - (N - i))] >= N - i;
  };

  auto check_prefix_B = [&](int i) -> bool {
    if (i == 0) return true;
    assert(N - i >= i);
    return z_prefix_B[N+1 + rev(2*i - 1)] >= i;
  };
  auto check_suffix_B = [&](int i) -> bool {
    if (i == N) return true;
    assert(i >= N - i);
    return z_suffix_B[N+1 + (i - (N - i))] >= N - i;
  };

  v = A; v.push_back(-1); for (auto x: BR) v.push_back(x);
  auto z_abr = z_function(v);
  v = AR; v.push_back(-1); for (auto x: B) v.push_back(x);
  auto z_arb = z_function(v);

  auto compare_prefix = [&](int i) -> bool {
    if (i < 0) return true;
    return z_abr[N+1 + rev(i)] >= i+1;
  };
  auto compare_suffix = [&](int i) -> bool {
    if (i >= N) return true;
    return z_arb[N+1 + i] >= N-i;
  };

  // maybe check i = 0 separately?
  int cnt_left = 0;
  F0R(i, N/2) cnt_left += A[i] < B[i];
  int cnt_right = 0;
  F0R(i, N/2) cnt_right += A[N-1-i] > B[N-1-i];
  F0R(i, N) {
    // A_i .. A_{N-1} B_1 .. B_{i-1}
    // B_i .. B_{N-1} A_1 .. A_{i-1}

    bool poss = cnt_left == N/2 && cnt_right == N/2;
    vector<int> vA, vB;
    for (int j = i; j < N; j++) {
      vA.push_back(A[j]);
      vB.push_back(B[j]);
    }
    for (int j = 0; j < i; j++) {
      vA.push_back(B[j]);
      vB.push_back(A[j]);
    }
    reverse(all(vB));
    poss &= vA == vB;

    //if (N-i >= i) {
    //  poss &= check_prefix_A(i); // A_0 .. A_{i-1} = rev(A_i .. A_{2i-2})
    //  poss &= compare_suffix(2*i); // A_{2i-1} .. A_{N-1} = rev(B_{len} .. B_{N-1})
    //  poss &= check_prefix_B(i); // B_0 .. B_{i-1} = rev(B_i .. B_{2i-2})
    //}
    //else {
    //  poss &= check_suffix_A(i); // A_i .. A_{N-1} = rev(A_{i-len} .. A_{i-1})
    //  poss &= compare_prefix(i - (N-i) - 1); // B_0 .. B_idx == rev(A_0 .. A_idx)
    //  poss &= check_suffix_B(i); // B_i .. B_{N-1} = rev(A_{i-len} .. A_{i-1})
    //}
    if (poss) return i;
    // update cnt_left, cnt_right
    cnt_left -= A[i] < B[i];
    cnt_left += A[i+N/2] < B[i+N/2];

    cnt_right -= A[N-N/2+i] > B[N-N/2+i];
    cnt_right += B[i] > A[i];
  }
  return -1;
}

int solve() {
  int N; cin >> N;
  vector<int> A(N); for (auto& x: A) cin >> x;
  vector<int> B(N); for (auto& x: B) cin >> x;

  int i1 = get_index(A, B);
  if (i1 != -1) return i1;
  else {
    int i2 = get_index(B, A);
    if (i2 != -1) return N + i2;
    else return -1;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  FOR(tc, 1, T+1) {
    cout << "Case #" << tc << ": " << solve() << '\n';
  }
}
