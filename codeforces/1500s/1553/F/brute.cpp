#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
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
// }}}


const int maxn = 3e5+5;
int N, A[maxn];

ll sum = 0, cur_sum = 0;
vector<int> toadds;

int on[maxn];
ll pfxCnt[maxn], pfxSum[maxn];

ll addSum(int x) {
  auto get_floors = [](int n) {
    vector<array<int, 3>> v;
    for (int i = 1, la; i <= n; i = la + 1) {
      la = n / (n / i);
      v.push_back({i, la, n/i});
    }
    return v;
  };
  auto v = get_floors(x);
  v.push_back({x+1, 300000, 0});

  ll res = 0;
  for (auto [l, r, d]: v) {
    res += (pfxCnt[r] - pfxCnt[l-1]) * x;
    res -= (pfxSum[r] - pfxSum[l-1]) * d;
  }
  return res;
}

ll addBigSum(int x) {
  ll res = 0;
  for (int i = 0; i <= 300000; i += x) {
    res += (pfxSum[min(300000, i+x-1)] - pfxSum[i]);
    res -= 1LL * i * (pfxCnt[min(300000, i+x-1)] - pfxCnt[i]);
  }
  return res;
}

void rebuild() {
  for (auto x: toadds) {
    on[x] = 1;
  }
  for (int i = 1; i <= 300000; i++) {
    pfxCnt[i] = pfxCnt[i-1] + on[i];
    pfxSum[i] = pfxSum[i-1] + (on[i] * i);
  }
  for (auto x: toadds) {
    sum += addSum(x);
    sum += addBigSum(x);
    // cout << "adding sum " << x << ": " << addSum(x) << ' ' << addBigSum(x) << endl;
  }
  cur_sum = 0;
  toadds.clear();
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N) {
    cin >> A[i];
  }

  vector<ll> ans(N);
  const int BLK = 450;
  F0R(i, N) {
    if (i % BLK == 0) {
      rebuild();
    }
    // cout << "after rebuild: " << sum << ' ' << cur_sum << endl;
    for (auto x: toadds) {
      cur_sum += x % A[i];
      cur_sum += A[i] % x;
    }
    cur_sum += addSum(A[i]);
    cur_sum += addBigSum(A[i]);
    // cout << i << ": " << addSum(A[i]) << ' ' << addBigSum(A[i]) << endl;
    toadds.push_back(A[i]);
    ans[i] = sum + cur_sum;
  }

  F0R(i, N) {
    cout << ans[i] << " \n"[i == N-1];
  }
}
