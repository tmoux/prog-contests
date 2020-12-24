#include <bits/stdc++.h>
using ll = long long;
using namespace std;

const ll INF = 1e18;
struct Cow {
  int x, y, id;
};

struct Event {
  int t, x, y, i, which;
  bool operator<(const Event& rhs) const {
    return t < rhs.t;
  }
};

int main() {
  int n; cin >> n;
  vector<Cow> E, N;
  for (int i = 0; i < n; i++) {
    char c; cin >> c;
    int x, y; cin >> x >> y;
    (c=='E'?E:N).push_back({x,y,i});
  }
  vector<ll> ans(n,INF);
  vector<Event> events;
  for (int i = 0; i < E.size(); i++) {
    for (int j = 0; j < N.size(); j++) {
      auto c = E[i];
      auto d = N[j];
      if (c.x < d.x && c.y > d.y) {
        int dx = d.x-c.x;
        int dy = c.y-d.y;
        if (dx != dy) {
          events.push_back({dx,d.x,c.y,i,0});
          events.push_back({dy,d.x,c.y,j,1});
        }
      }
    }
  }
  set<pair<int,int>> seen;
  vector<bool> aliveN(N.size(),true), aliveE(E.size(),true);
  sort(events.begin(),events.end());
  for (auto e: events) {
    auto& alive = e.which==0?aliveE:aliveN;
    auto& V = e.which==0?E:N;
    if (!alive[e.i]) continue;
    if (seen.count({e.x,e.y})) {
      ans[V[e.i].id] = e.t;
      alive[e.i] = false;
    }
    else {
      seen.insert({e.x,e.y});
    }
  }
  for (auto i: ans) {
    if (i < INF) {
      cout << i << '\n';
    }
    else {
      cout << "Infinity\n";
    }
  }
}
