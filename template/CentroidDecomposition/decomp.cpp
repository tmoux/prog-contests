bool blocked[maxn];
int sub_size[maxn];

int dfsSize(int i, int p) {
    sub_size[i] = 1;
    for (Edge e: adj[i]) {
        if (e.to == p || blocked[e.to]) continue;
        sub_size[i] += dfsSize(e.to,i);
    }
    return sub_size[i];
}
int getCentroid(int i, int p, int compSize) {
    for (Edge e: adj[i]) {
        if (e.to == p || blocked[e.to]) continue;
        if (sub_size[e.to] * 2 > compSize) return getCentroid(e.to,i,compSize);
    }
    return i;
}

void decomp(int i) {
    int compSize = dfsSize(i,i);
    int centroid = getCentroid(i,i,compSize);
    blocked[centroid] = true;
    for (Edge e: adj[centroid]) {
        if (blocked[e.to]) continue;
        decomp(e.to);
    }
}
