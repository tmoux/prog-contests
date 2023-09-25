//Randomness stuff, ckmin, ckmax are optional--depends on time
#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a,x) for (auto& a : x)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<pair<int, int>> X, Y;
ll ans = 0;

void F(int i, int j, int l, int r) {
  if (i > j) return;
  int m = (i + j) / 2;

  pair<ll, int> mx = {0, -1};
  for (int k = l; k <= r; k++) {
    if (X[k].first <= Y[m].first && X[k].second <= Y[m].second) {
      ll area = 1LL * (Y[m].first - X[k].first) * (Y[m].second - X[k].second);
      ckmax(mx, {area, k});
    }
  }
  ckmax(ans, mx.first);
  assert(mx.second != -1);

  F(i, m-1, l, mx.second);
  F(m+1, j, mx.second, r);
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int M, N; cin >> M >> N;
  vector<pair<int, int>> A(M), B(N);
  F0R(i, M) {
    cin >> A[i].first >> A[i].second;
  }
  F0R(i, N) {
    cin >> B[i].first >> B[i].second;
  }

  sort(all(A));
  for (auto [x, y]: A) {
    if (!X.empty() && X.back().second <= y) {
      continue;
    }
    else X.push_back({x, y});
  }
  sort(all(B));
  for (auto [x, y]: B) {
    auto it = lower_bound(all(X), make_pair(x, 0));
    if (it == X.begin() || prev(it)->second >= y) {
      continue;
    }
    else {
      while (!Y.empty() && Y.back().second <= y) {
        Y.pop_back();
      }
      Y.push_back({x, y});
    }
  }

  if (X.empty() || Y.empty()) {
    cout << 0 << '\n';
  }
  else {
    F(0, sz(Y)-1, 0, sz(X)-1);
    cout << ans << '\n';
  }
  return 0;
}


