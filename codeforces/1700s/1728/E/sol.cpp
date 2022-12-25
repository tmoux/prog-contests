#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
  template <class Fun>
    class y_combinator_result {
      Fun fun_;

      public:
      template <class T>
        explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

      template <class... Args>
        decltype(auto) operator()(Args &&...args) {
          return fun_(std::ref(*this), std::forward<Args>(args)...);
        }
    };

  template <class Fun>
    decltype(auto) y_combinator(Fun &&fun) {
      return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
    }
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
!is_same<T_container, string>::value,
  typename T_container::value_type>::type>
  ostream &operator<<(ostream &os, const T_container &v) {
    os << '[';
    string sep;
    for (const T &x : v) os << sep << x, sep = ", ";
    return os << ']';
  }
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

pair<int,pair<int,int>> gcd(int a, int b) {
  if (a == 0) return {b,{0,1}};
  if (b == 0) return {a,{1,0}};
  int x1 = 1, x2 = 0, y1 = 0, y2 = 1;
  while (a && b) {
    int r = a/b;
    int tmp = b;
    b = a - r * b;
    a = tmp;
    int tmpx = x2, tmpy = y2;
    x2 = x1 - r * x2;
    y2 = y1 - r * y2;
    x1 = tmpx, y1 = tmpy;
  }
  return {a,{x1,y1}};
}

// Functions to handle negative floor/ceil division
ll floor(ll a, ll b) {
  if (b < 0) return floor(-a, -b);
  if (a >= 0) return a / b;
  else return (a - b + 1) / b;
}

ll ceil(ll a, ll b){
	ll res=a/b;
	if(b*res!=a)res+=(a>0)&(b>0);
	return res;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<int> A(N), B(N), diffs;
  F0R(i, N) {
    cin >> A[i] >> B[i];
    diffs.push_back(A[i] - B[i]);
  }
  sort(all(diffs), greater<int>());

  vector<ll> numA(N+1);
  numA[0] = std::accumulate(all(B), 0LL);
  for (int i = 1; i <= N; i++) numA[i] = numA[i-1] + diffs[i-1];
  int peak = std::distance(numA.begin(), max_element(all(numA)));

  int M; cin >> M;
  vector<int> X(M), Y(M);

  auto query = [&](ll l, ll r, ll step) -> ll {
    if (r <= peak) return numA[r];
    else if (l >= peak) return numA[l];
    else {
      ll i = l + ((peak - l)/step) * step;
      assert(l <= i && i < r);
      ll ans = numA[i];
      if (i+step <= r) ckmax(ans, numA[i+step]);
      return ans;
    }
  };

  vector<ll> ans(M);
  F0R(i, M) {
    cin >> X[i] >> Y[i];
    auto [g, _] = gcd(X[i], Y[i]);
    if (N % g != 0) {
      ans[i] = -1;
    }
    else {
      ll NN = N / g;
      X[i] /= g;
      Y[i] /= g;
      auto [ng, p] = gcd(X[i], Y[i]);
      auto [p1, p2] = p;
      ll P = NN * p1;
      ll Q = NN * p2;
      assert(P * X[i] + Q * Y[i] == NN);

      ll t1 = ceil(-P, Y[i]);
      ll t2 = floor(Q, X[i]);

      if (t1 <= t2) {
        ll l     = g * (P+Y[i]*t1) * X[i];
        ll r     = g * (P+Y[i]*t2) * X[i];
        ll step  = 1LL * g * X[i] * Y[i];
        ans[i] = query(l, r, step);
      }
      else ans[i] = -1;
    }
  }

  F0R(i, M) cout << ans[i] << '\n';
}
