#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
bool adj[maxn][maxn];
int n;

bool vis[maxn];
vector<int> v;
void dfs(int i, int p) {
  vis[i] = true;
  for (int j = 0; j < n; j++) {
    if (adj[i][j] && !vis[j]) {
      dfs(j,i);
    }
  }
  v.push_back(i);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n;
  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    for (int j = 0; j < n; j++) {
      adj[i][j] = s[j] == '1';
    }
  }
  dfs(0,0);
  if (v.size() < n) {
    cout << "impossible\n";
  }
  else {
    for (int i: v) {
      cout << i << ' ';
    }
    cout << '\n';
  }
}

