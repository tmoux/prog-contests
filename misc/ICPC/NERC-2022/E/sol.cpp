#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

typedef pair<int, int> pi;
typedef pair<ll, ll> pl;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<ld> vd;
typedef vector<pi> vpi;
typedef vector<pl> vpl;

#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= (a); i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define trav(a, v) for (auto& a : v)

#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

const char nl = '\n';

const int maxn = 1e5 + 5;
int N, L;
int a[maxn];

vector<array<int, 2>> check_min(int k) {
  vector<array<int, 2>> ret;
  int leftBound = 0;
  F0R(i, N) {
    int l = max(leftBound, a[i] - k);
    int r = l + k;
    if (!(l <= a[i] && a[i] <= r && r <= L)) {
      return {};
    } else {
      ret.push_back({l, r});
    }
    leftBound = r;
  }
  return ret;
}

vector<array<int, 2>> check_ans(int mn, int mx,
                                const vector<array<int, 2>>& v) {
  int total = 0;
  vector<array<int, 2>> ret;
  int rightBound = L;
  for (int i = N - 1; i >= 0; i--) {
    int r = rightBound;
    if (r - mx > a[i]) return {};
    int l = max(i==0?0:v[i-1][1], r-mx);
    ret.push_back({l, r});
    total += r-l;
    rightBound = l;
  }

  if (total == L) {
    reverse(all(ret));
    return ret;
  } else {
    return {};
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> L >> N;
  F0R(i, N) { cin >> a[i]; }
  int lo = 0, hi = L + 1;
  vector<array<int, 2>> starts;
  while (lo + 1 < hi) {
    int mid = (lo + hi) / 2;
    auto v = check_min(mid);
    if (v.empty()) {
      hi = mid;
    } else {
      starts = v;
      lo = mid;
    }
  }
  assert(!starts.empty());
  int mn = lo;

  lo = mn - 1;
  hi = L + 1;
  vector<array<int, 2>> ans;
  while (lo + 1 < hi) {
    int mid = (lo + hi) / 2;
    auto v = check_ans(mn, mid, starts);
    if (v.empty()) {
      lo = mid;
    } else {
      ans = v;
      hi = mid;
    }
  }

  assert(!ans.empty());

  // output
  for (auto [l, r] : ans) {
    cout << l << ' ' << r << '\n';
  }
}
