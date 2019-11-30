const int maxn = 1e5+5;
const int maxk = 18;
int par[maxk][maxn];

void root(int i, int p) {
    for (Edge& e: mst[i]) {
        if (e.to == p) continue;
        depth[e.to] = depth[i] + 1;
        par[0][e.to] = i;
        for (int k = 1; k < maxk; k++) {
            par[k][e.to] = par[k-1][par[k-1][e.to]];
        }
        root(e.to,i);
    }
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a,b);
    for (int k = maxk - 1; k >= 0; k--) {
        int bb = par[k][b];
        if (bb != 0 && depth[bb] >= depth[a])
            b = bb;
    }
    if (a == b) return a;
    for (int k = maxk - 1; k >= 0; k--) {
        int aa = par[k][a];
        int bb = par[k][b];
        if (aa != bb) {
            a = aa;
            b = bb;
        }
    }
    return par[0][a];
}

