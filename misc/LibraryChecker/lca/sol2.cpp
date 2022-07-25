#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 5;
const int maxk = 20;
int par[maxk][maxn];
int depth[maxn];
vector<int> adj[maxn];

void root(int i, int p)
{
  for (int j : adj[i])
  {
    if (j == p)
      continue;
    depth[j] = depth[i] + 1;
    par[0][j] = i;
    for (int k = 1; k < maxk; k++)
    {
      par[k][j] = par[k - 1][j] == -1 ? -1 : par[k - 1][par[k - 1][j]];
    }
    root(j, i);
  }
}

int lca(int a, int b)
{
  if (depth[a] > depth[b])
    swap(a, b);
  for (int k = maxk - 1; k >= 0; k--)
  {
    int bb = par[k][b];
    if (bb != 0 && depth[bb] >= depth[a])
      b = bb;
  }
  if (a == b)
    return a;
  for (int k = maxk - 1; k >= 0; k--)
  {
    int aa = par[k][a];
    int bb = par[k][b];
    if (aa != bb)
    {
      a = aa;
      b = bb;
    }
  }
  return par[0][a];
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int N, Q;
  cin >> N >> Q;
  for (int i = 1; i < N; i++)
  {
    int p;
    cin >> p;
    adj[i].push_back(p);
    adj[p].push_back(i);
  }
  root(0, 0);
  while (Q--)
  {
    int u, v;
    cin >> u >> v;
    cout << lca(u, v) << '\n';
  }
}