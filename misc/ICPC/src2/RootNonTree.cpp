void dfs(int u){
  static int top;
  stk[++top] = u;
  for (int i = 0;i < g[u].size();i++){
    int v = g[u][i];
    if (v != p[u]){
        p[v] = u;
        dfs(v);
        if (siz[u] + siz[v] >= magic){
          siz[u] = 0;
          tot_cols++;
          cap[tot_cols] = u;
          while (stk[top] != u){
            col[stk[top--]] = tot_cols;
          }
        }
        else siz[u] += siz[v];
    }
  }
  siz[u]++;
}

void paint(int u,int c){
    if (col[u]) c = col[u];
    else col[u] = c;
    for (int i = 0;i < g[u].size();i++){
        int v = g[u][i];
        if (v != p[u]){
            paint(v,c);
        }
    }
}
//actual blokcing; magic = block size
dfs(1);
if (!tot_cols){
    cap[++tot_cols] = 1;
}
paint(1,tot_cols);
