//belong is a DSU; unit = union
int n, match[N], next[N], mark[N], vis[N], Q[N];
std::vector<int> e[N];
int rear;

int LCA(int x, int y){
  static int t = 0; t++;
  while (true) {
    if (x != -1) {
      x = findb(x);
      if (vis[x] == t) return x;
      vis[x] = t;
      if (match[x] != -1) x = next[match[x]];
      else x = -1;
    }
    std::swap(x, y);
  }
}

void group(int a, int p){
    while (a != p){
      int b = match[a], c = next[b];
      if (findb(c) != p) next[c] = b;
      if (mark[b] == 2) mark[Q[rear++] = b] = 1;
      if (mark[c] == 2) mark[Q[rear++] = c] = 1;
      unit(a, b); unit(b, c);
      a = c;
    }
}

void aug(int s){
  for (int i = 0; i < n; i++)
    next[i] = -1, belong[i] = i, mark[i] = 0, vis[i] = -1;
  mark[s] = 1;
  Q[0] = s; rear = 1;
  for (int front = 0; match[s] == -1 && front < rear; front++){
    int x = Q[front];
    for (int i = 0; i < (int)e[x].size(); i++){
      int y = e[x][i];
      if (match[x] == y) continue;
      if (findb(x) == findb(y)) continue;
      if (mark[y] == 2) continue;
      if (mark[y] == 1){
        int r = LCA(x, y);
        if (findb(x) != r) next[x] = y;
        if (findb(y) != r) next[y] = x;
        group(x, r);
        group(y, r);
      }
      else if (match[y] == -1){
        next[y] = x;
        for (int u = y; u != -1; ){
          int v = next[u];
          int mv = match[v];
          match[v] = u, match[u] = v;u = mv;
        }
        break;
      }
      else{
        next[y] = x;
        mark[Q[rear++] = match[y]] = 1;
        mark[y] = 2;
      }
    }
  }
}
//the graph is stored as e[N] and g[N]
for (int i = 0; i < n; i++) match[i] = -1;
for (int i = 0; i < n; i++) if (match[i] == -1) aug(i);
int tot = 0;
for (int i = 0; i < n; i++){
  if (match[i] != -1) tot++;
}
//matched pairs = tot/2
printf("%d\n", tot/2);
for (int i = 0; i < n; i++){
    printf("%d ", match[i] + 1);
}
