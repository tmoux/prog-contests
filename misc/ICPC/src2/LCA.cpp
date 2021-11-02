int L; //SET THIS TO CEIL(LOG(MX_N))
int anc[MX][L];
int depth[MX];
int parent[MX];

int LCA(int a, int b) {
    if (depth[a] < depth[b]) {
        int c = b;
        b = a;
        a = c;
    }

    int dist = depth[a] - depth[b];
    while (dist > 0) {
        F0R(i, L) {
            if (dist & 1 << i) {
                a = anc[a][i];
                dist -= 1 << i;
            }
        }
    }

    if (a == b) return a;

    F0Rd(j, L) {
        if (anc[a][j] != -1 && anc[a][j] != anc[b][j]) {
            a = anc[a][j]; b = anc[b][j];
        }
    }
    return parent[a];
}

void preprocess() {
    //make sure to compute parents and depths
    F0R(i, N) F0R(j, L) anc[i][j] = -1;
    F0R(i, N) anc[i][0] = parent[i];
    FOR(j, 1, L) {
        F0R(i, N) {
            if (anc[i][j-1] != -1) {
                anc[i][j] = anc[anc[i][j-1]][j-1];
            }
        }
    }
}
