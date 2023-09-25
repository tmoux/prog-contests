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

struct Event {
  int r, c, ty, id;
  bool operator<(const Event& rhs) const {
    if (r != rhs.r) return r < rhs.r;
    if (c != rhs.c) return c < rhs.c;
    return ty < rhs.ty; // 0 = start comes before 1
  }
};

void imposs() {
  cout << "syntax error" << '\n';
  exit(0);
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int N; cin >> N;
  vector<Event> events;
  vector<array<int, 2>> open(N), close(N);
  F0R(i, N) {
    int r, c; cin >> r >> c;
    events.push_back({r, c, 0, i});
    open[i] = {r, c};
  }
  F0R(i, N) {
    int r, c; cin >> r >> c;
    events.push_back({r, c, 1, i});
    close[i] = {r, c};
  }
  sort(all(events));
  set<pair<int, int>> opens; // column, id
  vector<int> ans(N);

  map<int, vector<pi>> horiz, vert;
  struct E {
    int isStart, r, c, id;
    bool operator<(const E& rhs) const {
      return r < rhs.r;
    }
  };

  vector<E> verts;
  vector<pair<int, array<int, 3>>> queries;
  for (auto [r, c, ty, id]: events) {
    if (ty == 0) {
      opens.insert({c, id});
    }
    else {
      auto it = opens.lower_bound({c+1, -1});
      if (it == opens.begin()) imposs();
      else {
        auto [oc, oid] = *prev(it);
        opens.erase(prev(it));
        ans[oid] = id;
        auto [a, b] = open[oid];
        auto [c, d] = close[id];

        horiz[a].push_back({b, d});
        if (a < c)
          horiz[c].push_back({b, d});

        vert[b].push_back({a, c});
        if (b < d)
          vert[d].push_back({a, c});

        verts.push_back({1, a, b, oid});
        if (b < d)
          verts.push_back({1, a, d, oid});

        verts.push_back({0, c+1, b, oid});
        if (b < d)
          verts.push_back({0, c+1, d, oid});

        queries.push_back({a, {b, d, oid}});
        if (a < c)
          queries.push_back({c, {b, d, oid}});
      }
    }
  }

  // Check parallel lines intersection.
  for (auto& [_, v]: horiz) {
    sort(all(v));
    for (int i = 1; i < sz(v); i++) {
      if (v[i].first <= v[i-1].second) imposs();
    }
  }
  for (auto& [_, v]: vert) {
    sort(all(v));
    for (int i = 1; i < sz(v); i++) {
      if (v[i].first <= v[i-1].second) imposs();
    }
  }

  // Check horizontal and vertical intersection
  sort(all(verts));
  int idx = 0;
  sort(all(queries));
  set<pair<int, int>> S; // column, id
  for (auto [r, p]: queries) {
    auto [a, b, id] = p;
    while (idx < sz(verts) && verts[idx].r <= r) {
      auto [isStart, R, C, id] = verts[idx++];
      if (isStart) {
        S.insert({C, id});
      }
      else {
        assert(S.count({C, id}));
        S.erase({C, id});
      }
    }
    for (auto it = S.lower_bound({a, 0}); it != S.end() && it->first <= b; ++it) {
      if (it->second != id) imposs();
    }
  }

  // Output
  F0R(i, N) {
    cout << ans[i]+1 << '\n';
  }

  return 0;
}


