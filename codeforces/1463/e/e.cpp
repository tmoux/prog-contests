#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, k;
vector<int> adj[maxn];
int dep[maxn];
int deg[maxn];

void NO() {
  cout << 0 << '\n';
  exit(0);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    int pi; cin >> pi;
    if (pi > 0) {
      adj[i].push_back(pi);
      ++deg[pi];
    }
  }
  for (int i = 0; i < k; i++) {
    int x, y; cin >> x >> y;
    dep[y] = x;
    adj[y].push_back(x);
    ++deg[x];
  }
  vector<int> ord(n+1,0), v;
  queue<pair<int,int>> q;
  for (int i = 1; i <= n; i++) {
    if (deg[i] == 0) q.push({0,i});
  }
  while (!q.empty()) {
    auto p = q.front(); q.pop();
    int i = p.second;
    int o = p.first;
    //cout << i << ": " << o << endl;
    ord[i] = o;
    v.push_back(i);
    for (int j: adj[i]) {
      if (--deg[j] == 0) {
        q.push({o+1,j});
      }
    }
  }
  if (v.size() < n) NO();
  reverse(v.begin(),v.end());
  vector<int> mp(n+1);
  vector<vector<int>> chain(n+1);
  for (int i: v) {
    mp[i] = dep[i]?mp[dep[i]]:i;
    chain[mp[i]].push_back(i);
  }

  vector<vector<int>> adj2(n+1);
  vector<int> deg2(n+1);
  for (int i = 1; i <= n; i++) {
    for (int j: adj[i]) {
      if (mp[i] != mp[j]) {
        adj2[mp[i]].push_back(mp[j]);
        ++deg2[mp[j]];
      }
    }
  }

  vector<int> ans;
  queue<int> q2;
  for (int i = 1; i <= n; i++) {
    if (!chain[i].empty() && deg2[i] == 0) {
      q2.push(i);
    }
  }
  while (!q2.empty()) {
    int f = q2.front(); q2.pop();
    //cout << f << endl;
    reverse(chain[f].begin(),chain[f].end());
    for (int j: chain[f]) {
      ans.push_back(j);
    }
    for (int j: adj2[f]) {
      if (--deg2[j] == 0) {
        q2.push(j);
      }
    }
  }
  if (ans.size() < n) NO();
  reverse(ans.begin(),ans.end());
  for (int i: ans) {
    cout << i << ' ';
  }
  cout << '\n';
}
