#include <bits/stdc++.h>
using ll = long long;
using namespace std;

const ll INF = 1e18;
struct Cow {
  int x, y, id;
};

struct Event {
  int t, x, y, i;
  bool operator<(const Event& rhs) const {
    return t < rhs.t;
  }
};

void dfs(int i, vector<vector<int>>& adj, vector<int>& blame) {
  for (int j: adj[i]) {
    dfs(j,adj,blame);
    blame[i] += blame[j];
  }
}

int main() {
  int n; cin >> n;
  vector<Cow> E, N;
  for (int i = 0; i < n; i++) {
    char c; cin >> c;
    int x, y; cin >> x >> y;
    (c=='E'?E:N).push_back({x,y,i});
  }
  vector<Event> events;
  for (int i = 0; i < E.size(); i++) {
    for (int j = 0; j < N.size(); j++) {
      auto c = E[i];
      auto d = N[j];
      if (c.x < d.x && c.y > d.y) {
        int dx = d.x-c.x;
        int dy = c.y-d.y;
        if (dx != dy) {
          events.push_back({dx,d.x,c.y,c.id});
          events.push_back({dy,d.x,c.y,d.id});
        }
      }
    }
  }
  map<pair<int,int>,int> seen;
  vector<bool> alive(n,true);
  vector<int> blame(n,0);
  vector<vector<int>> adj(n);
  sort(events.begin(),events.end());
  for (auto e: events) {
    if (!alive[e.i]) continue;
    if (seen.count({e.x,e.y})) {
      int stop = seen[make_pair(e.x,e.y)];
      blame[stop]++;
      adj[stop].push_back(e.i);
      alive[e.i] = false;
    }
    else {
      seen[make_pair(e.x,e.y)] = e.i;
    }
  }
  for (int i = 0; i < n; i++) {
    if (alive[i]) dfs(i,adj,blame);
  }
  for (int i = 0; i < n; i++) {
    cout << blame[i] << '\n';
  }
}
