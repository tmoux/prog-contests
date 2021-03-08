#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;

vector<vector<int>> to;
vector<int> indegree;

vector<bool> rem;
void dfs(int i, int& cnt) {
  rem[i] = true;
  cnt++;
  for (int j: to[i]) {
    if (!rem[j]) {
      dfs(j,cnt);
    }
  }
}

const int maxn = 105;
vector<int> inn[maxn], out[maxn];
vector<int> condense[maxn], rev[maxn];
bool visited[maxn];
int sz[maxn];
int comp[maxn];
deque<int> L;

void visit(int now) {
    if (!visited[now]) {
        visited[now] = true;
        for (int j: inn[now]) {
            visit(j);
        }
        L.push_front(now);
    }
}

void assign(int u, int root) {
    if (comp[u] == -1) {
        comp[u] = root;
        sz[root]++;
        for (int j: out[u]) {
            assign(j,root);
        }
    }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  to.resize(n);
  indegree.resize(n);
  rem.resize(n,false);
  vector<string> understand(n);
  vector<set<string>> others(n);
  string s;
  getline(cin,s);
  for (int i = 0; i < n; i++) {
    getline(cin,s);
    stringstream ss(s);
    string name, under; ss >> name >> under;
    string other;
    understand[i] = under;
    others[i].insert(under);
    while (ss >> other) {
      if (under != other) {
        others[i].insert(other);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j && others[i].count(understand[j])) {
        inn[i].push_back(j);
        out[j].push_back(i);
      }
    }
  }
  memset(comp,-1,sizeof comp);
  //Kosaraju
  for (int i = 0; i < n; i++) {
      visit(i);
  }
  for (int u: L) {
      assign(u,u);
  }
  int ans = 0;
  for (int i = 0; i < n; i++) {
    ans = max(ans,sz[comp[i]]);
  }
  cout << (n-ans) << '\n';
}
