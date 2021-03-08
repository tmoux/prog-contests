#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int INF = 1e9+9;
const int maxn = 1e5+5;
const int maxr = 29;
int n, k;

int cv(int i, int r) {
  return i*(maxr+1)+(r+1);
}

vector<int> adj[maxn*(maxr+1)];

int x[maxn];

struct topk {
  set<pair<int,int>> s; //weight, x-coord
  void insert(int x, int wt) {
    if (x != 0) {
      s.insert({wt,x});
    }
  }
  void erase(int x, int wt) {
    if (s.count({wt,x})) s.erase({wt,x});
  }
  vector<int> edges() { //returns list of ones that can be focused on
    vector<int> ret;
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
      ret.push_back(it->second);
      if (ret.size() == k) break;
    }
    return ret;
  }
};

bool in(int x, int r, int y) {
  return (x-(1<<r)) <= y && y <= (x+(1<<r));
}

bool canSee[maxn*(maxr+1)];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> k;
  vector<pair<int,int>> points; //x-coord, weight
  points.push_back({0,-1});
  map<int,int> MP;
  for (int i = 0; i < n; i++) {
    cin >> x[i];
    points.push_back({x[i],i});
  }
  sort(points.begin(),points.end());
  for (int i = 0; i < points.size(); i++) {
    MP[points[i].first] = i;
  }
  //build graph
  for (int r = 0; r < maxr; r++) {
    topk topk;
    int L = 0, R = 0;
    for (auto p: points) {
      int x = p.first;
      while (L < points.size() && !in(x,r,points[L].first)) {
        topk.erase(points[L].first,points[L].second);
        L++;
      }
      while (R < points.size() && in(x,r,points[R].first)) {
        topk.insert(points[R].first,points[R].second);
        R++;
      }
      //[L,R)
      bool can = false;
      auto edges = topk.edges();
      for (auto ne : edges) {
        adj[cv(MP[x],r)].push_back(cv(MP[ne],r));
        if (ne == x) can = true;
      }
      canSee[cv(MP[x],r)] = can;
      /*
      if (r == 0) {
        cout << "x = " << x << '\n';
        for (auto ne: edges) {
          cout << ne << ' ';
        }
        cout << '\n';
        cout << "L = " << points[L].first << ", R = " << points[R].first << '\n';
      }
      */
    }
  }
  for (int r = -1; r < maxr; r++) {
    for (auto p: points) {
      int x = p.first;
      if (r-1 >= -1) 
        adj[cv(MP[x],r)].push_back(cv(MP[x],r-1));
      if (r+1 < maxr)
        adj[cv(MP[x],r)].push_back(cv(MP[x],r+1));
    }
  }

  /*
  for (auto p: points) {
    int x = p.first;
    for (int r = -1; r <= 6; r++) {
      cout << x << ' ' << r << ":\n";
      for (auto j: adj[make_pair(x,r)]) {
        cout << j.first << ' ' << j.second << '\n';
      }
      cout << '\n';
    }
  }
  */
  //bfs
  int start = cv(MP[0],0);
  // r \in [-1,maxr]
  vector<int> dist(maxn*(maxr+1),INF);
  queue<int> q;  
  q.push(start);
  dist[start] = 0;
  while (!q.empty()) {
    auto f = q.front(); q.pop();
    for (auto j: adj[f]) {
      if (dist[f] + 1 < dist[j]) {
        dist[j] = dist[f] + 1;
        q.push(j);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    int ans = INF;
    for (int r = -1; r < maxr; r++) {
      if (r==-1 || canSee[cv(MP[x[i]],r)])
        ans = min(ans,dist[cv(MP[x[i]],r)]);
    }
    cout << (ans < INF ? ans : -1) << '\n';
  }
}
