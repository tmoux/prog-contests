#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using ll = long long;
#define int ll

vector<vector<int>> capacity, flow;
vector<int> height, excess;
const int inf = 1e18;
int n, m, s, t, u, v, c, amount;

void push(int u, int v)
{
  int d = min(excess[u], capacity[u][v] - flow[u][v]);
  flow[u][v] += d;
  flow[v][u] -= d;
  excess[u] -= d;
  excess[v] += d;
}

void relabel(int u)
{
  int d = inf;
  for (int i = 0; i < n; i++) {
    if (capacity[u][i] - flow[u][i] > 0)
      d = min(d, height[i]);
  }
  if (d < inf)
    height[u] = d + 1;
}

vector<int> find_max_height_vertices(int s, int t) {
  vector<int> max_height;
  for (int i = 0; i < n; i++) {
    if (i != s && i != t && excess[i] > 0) {
      if (!max_height.empty() && height[i] > height[max_height[0]])
        max_height.clear();
      if (max_height.empty() || height[i] == height[max_height[0]])
        max_height.push_back(i);
    }
  }
  return max_height;
}

int max_flow(int s, int t)
{
  height.assign(n, 0);
  height[s] = n;
  flow.assign(n, vector<int>(n, 0));
  excess.assign(n, 0);
  excess[s] = inf;
  for (int i = 0; i < n; i++) {
    if (i != s)
      push(s, i);
  }

  vector<int> current;
  while (!(current = find_max_height_vertices(s, t)).empty()) {
    for (int i : current) {
      bool pushed = false;
      for (int j = 0; j < n && excess[i]; j++) {
        if (capacity[i][j] - flow[i][j] > 0 && height[i] == height[j] + 1) {
          push(i, j);
          pushed = true;
        }
      }
      if (!pushed) {
        relabel(i);
        break;
      }
    }
  }

  int max_flow = 0;
  for (int i = 0; i < n; i++)
    max_flow += flow[i][t];
  return max_flow;
}


int32_t main(){

  cin >> n;
  cin >> m;
  cin >> s;
  cin >> t;
  amount = 0;
  capacity = vector<vector<int>>(n, vector<int>(n));

  for (int i = 0; i < m; i++){
    cin >> u;
    cin >> v;
    cin >> c;   //capacity from u to v
    capacity[u][v] += c; 
  }

  int max = max_flow(s, t);

  queue<int> q;
  q.push(s);
  vector<bool> vis(n, false);
  vis[s] = true;

  int cnt = 0;
  while (!q.empty()) {
    int f = q.front(); q.pop();
    cnt++;
    for (int i = 0; i < n; i++) {
      if (!vis[i] && capacity[f][i] - flow[f][i] > 0) {
        vis[i] = true;
        q.push(i);
      }
    }
  }

  cout << cnt << '\n';
  for (int i = 0; i < n; i++) {
    if (vis[i]) cout << i << '\n';
  }
  return 0;
}
