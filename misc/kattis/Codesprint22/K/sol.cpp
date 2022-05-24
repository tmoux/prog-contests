#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//implement DSU with rollbacks
//when rolling back change (a,b) (a is parent of b):
//a.szX -= b.szX, a.szY -= b.szY
//Reset b to be the parent of itself
//use random merging
const int maxn = 2e5+5;
int N, M, K, T;
int ans[maxn+5];

struct Node //node in segment tree of queries
{
  int se, en;
  vector<pair<int,int>> edges;
  //edges that are present in this node
} nodes[4*maxn+5];

void build(int i, int se, int en) {
  nodes[i].se = se;
  nodes[i].en = en;
  if (se == en) return;
  int m = (se+en)>>1;
  build(i*2,se,m);
  build(i*2+1,m+1,en);
}

void addInterval(int i, int l, int r, const pair<int,int>& p) {
  if (l <= nodes[i].se && nodes[i].en <= r) {
    nodes[i].edges.push_back(p);
    return;
  }
  if (nodes[i].se == nodes[i].en) return;
  int mid = (nodes[i].se+nodes[i].en)/2;
  if (mid >= l) addInterval(i*2,l,r,p);
  if (mid < r) addInterval(i*2+1,l,r,p);
}

stack<int> active;
//DSU information
int parent[2*maxn+10];
int sz[2*maxn+10];

int findParent(int i) {
  if (parent[i] == i) return i;
  return findParent(parent[i]);
}

void merge(int a, int b) {
  a = findParent(a);
  b = findParent(b);
  if (a == b) return;
  if (sz[a] < sz[b]) swap(a,b);
  parent[b] = a;
  sz[a] += sz[b];
  active.push(b);
}

void rollback() {
  int b = active.top(); active.pop();
  int a = parent[b];
  parent[b] = b;
  sz[a] -= sz[b];
}

void DFS(int i) {
  int t0 = active.size();
  //add this interval's edges
  for (const auto& p: nodes[i].edges) {
    merge(p.first,p.second);
  }
  if (nodes[i].se == nodes[i].en) {
    ans[nodes[i].se] = findParent(K) == findParent(1);
  }
  else {
    DFS(i*2);
    DFS(i*2+1);
  }
  //at the end, rollback edges
  while ((int)active.size() > t0) {
    rollback();
  }
}

vector<pair<int,int>> adj[maxn];

int color[maxn];
void dfs(int i, int c) {
  if (color[i] != -1) return;
  else {
    color[i] = c;
    for (auto [j, d]: adj[i]) {
      if (color[j] != -1) {
        assert(color[j] == (c^d));
      }
      else {
        dfs(j, c^d);
      }
    }
  }
}

int main()
{
  ios_base::sync_with_stdio(false); cin.tie(0);
  cin >> N >> M >> K >> T;
  build(1,1,M);
  for (int i = 1; i <= M; i++) {
    int a, b; cin >> a >> b;
    string s; cin >> s;
    pair<int,int> p = {a, b};
    if (s == "imposter") {
      adj[a].push_back({b, 1});
      adj[b].push_back({a, 1});
    }
    else {
      adj[a].push_back({b, 0});
      adj[b].push_back({a, 0});
    }
    if (i-T >= 1) {
      addInterval(1, 1, i-T, p);
      // printf("Adding %d %d from [%d, %d]\n", a, b, 1, i-T);
    }
    if (i+1 <= M) {
      addInterval(1, i+1, M, p);
      // printf("Adding %d %d from [%d, %d]\n", a, b, i+1, M);
    }
  }

  //initialize DSU
  for (int i = 1; i <= N; i++) {
    parent[i] = i;
    sz[i] = 1;
  }
  //DFS on segment tree
  DFS(1);
  //output

  int mint = -1;
  for (int i = 1; i <= M-T+1; i++) {
    if (ans[i]) {
      mint = i;
      break;
    }
  }
  if (mint == -1) {
    cout << -1 << '\n';
  }
  else {
    memset(color, -1, sizeof color);
    dfs(1, 0);
    cout << mint << ' ' << (color[K] == 0 ? "crewmate" : "imposter") << '\n';
  }
}
