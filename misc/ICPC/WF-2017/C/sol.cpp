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

bool dfs(int a, int L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
  if (A[a] != L) return 0;
  A[a] = -1;
  for (int b: g[a]) if (B[b] == L + 1) {
      B[b] = 0;
      if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
        return btoa[b] = a, 1;
    }
  return 0;
}

int hopcroftKarp(vector<vi>& g, vi& btoa) {
  int res = 0;
  vi A(g.size()), B(btoa.size()), cur, next;
  for (;;) {
    fill(all(A), 0);
    fill(all(B), 0);
    cur.clear();
    for (int a : btoa) if (a != -1) A[a] = -1;
    FOR(a,0,sz(g)) if (A[a] == 0) cur.push_back(a);
    for (int lay = -1;; lay++) {
      bool islast = 0;
      next.clear();
      for (int a : cur) for (int b : g[a]) {
          if (btoa[b] == -1) {
            B[b] = lay;
            islast = -1;
          }
          else if (btoa[b] != a && !B[b]) {
            B[b] = lay;
            next.push_back(btoa[b]);
          }
        }
      if (islast) break;
      if (next.empty()) return res;
      for (int a : next) A[a] = lay;
      cur.swap(next);
    }
    FOR(a,0,sz(g))
      res += dfs(a, 0, g, btoa, A, B);
  }
}

bool dfs(int a, int L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
  if (A[a] != L) return 0;
  A[a] = -1;
  for (int b : g[a]) if (B[b] == L + 1) {
      B[b] = 0;
      if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
        return btoa[b] = a, 1;
    }
  return 0;
}

int hopcroftKarp(vector<vi>& g, vi& btoa) {
  int res = 0;
  vi A(g.size()), B(btoa.size()), cur, next;
  for (;;) {
    fill(all(A), 0);
    fill(all(B), 0);
    cur.clear();
    for (int a : btoa) if (a != -1) A[a] = -1;
    FOR(a,0,sz(g)) if(A[a] == 0) cur.push_back(a);
    for (int lay = 1;; lay++) {
      bool islast = 0;
      next.clear();
      for (int a : cur) for (int b : g[a]) {
          if (btoa[b] == -1) {
            B[b] = lay;
            islast = 1;
          }
          else if (btoa[b] != a && !B[b]) {
            B[b] = lay;
            next.push_back(btoa[b]);
          }
        }
      if (islast) break;
      if (next.empty()) return res;
      for (int a : next) A[a] = lay;
      cur.swap(next);
    }
    FOR(a,0,sz(g))
      res += dfs(a, 0, g, btoa, A, B);
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int N, M; cin >> N >> M;
  vector<vector<int>> A(N, vector<int>(M));
  ll ans = 0;
  F0R(i, N) {
    F0R(j, M) {
      cin >> A[i][j];
      ans += A[i][j];
      if (A[i][j] > 0) ans--;
    }
  }

  map<int, pair<vector<int>, vector<int>>> mp;
  F0R(i, N) {
    int m = 0;
    F0R(j, M) {
      ckmax(m, A[i][j]);
    }
    if (m == 0) continue;
    mp[m].first.push_back(i);
  }
  F0R(j, M) {
    int m = 0;
    F0R(i, N) {
      ckmax(m, A[i][j]);
    }
    if (m == 0) continue;
    mp[m].second.push_back(j);
  }

  for (const auto& [x, p]: mp) {
    const auto& rows = p.first;
    const auto& cols = p.second;

    vector<vi> g(N);
    for (int i: rows) {
      for (int j: cols) {
        if (A[i][j] > 0) {
          g[i].push_back(j);
        }
      }
    }

    vi btoa(M, -1);
    int max_matching = hopcroftKarp(g, btoa);
    ans -= 1LL * (x - 1) * (sz(rows) + sz(cols) - max_matching);
  }
  cout << ans << '\n';

  return 0;
}


