#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, maxk = 18;
int n, q;
vector<int> adj[maxn];
int depth[maxn], parent[maxk][maxn];
int preorder[maxn], inv[maxn], pre = 0;

int lca(int a, int b) { //returns depth of lca
    if (depth[a] > depth[b]) swap(a,b);
    for (int k = maxk - 1; k >= 0; k--) {
        int bb = parent[k][b];
        if (bb != -1 && depth[bb] >= depth[a]) b = bb;
    }
    if (a == b) return a;
    for (int k = maxk - 1; k >= 0; k--) {
        int aa = parent[k][a], bb = parent[k][b];
        if (aa != bb) a = aa, b = bb;
    }
    return parent[0][a];
}

//segtree
int mn[4*maxn], mx[4*maxn], s[4*maxn], e[4*maxn];
void build(int i, int l, int r) {
    s[i] = l, e[i] = r;
    if (l == r) {
        mn[i] = preorder[l];
        mx[i] = preorder[l];
        return;
    }
    int m = (l+r)>>1;
    build(i*2,l,m);
    build(i*2+1,m+1,r);
    mn[i] = min(mn[i*2],mn[i*2+1]);
    mx[i] = max(mx[i*2],mx[i*2+1]);
    /*
    cout << l << ' ' << r << "\n";
    printf("mn: %d\nidx: %d\nmn2: %d\n",seg[i].mn,seg[i].idx,seg[i].mn2);
    */
}

int getmin(int i, int l, int r) {
    if (e[i] < l || s[i] > r) return n;    
    if (l <= s[i] && e[i] <= r) return mn[i];
    return min(getmin(i*2,l,r),getmin(i*2+1,l,r));
}

int getmax(int i, int l, int r) {
    if (e[i] < l || s[i] > r) return 0;    
    if (l <= s[i] && e[i] <= r) return mx[i];
    return max(getmax(i*2,l,r),getmax(i*2+1,l,r));
}

void dfs(int i, int p, int d) {
    inv[pre] = i;
    preorder[i] = pre++;
    parent[0][i] = p;
    depth[i] = d;
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i,d+1);        
    }
}

int ss[4*maxn], ee[4*maxn], seg[4*maxn];
void buildLCA(int i, int l, int r) {
    ss[i] = l, ee[i] = r;
    if (l == r) {
        seg[i] = lca(l,l+1);
        //cout << l << ' ' << r <<  ": " << seg[i] << '\n';
        return;
    }
    int m = (l+r)>>1;
    buildLCA(i*2,l,m);
    buildLCA(i*2+1,m+1,r);
    seg[i] = lca(seg[i*2],seg[i*2+1]);
    //cout << l << ' ' << r << ": " << seg[i] << '\n';
}

int query(int i, int l, int r) {
    if (l == r+1) return l;
    if (ee[i] < l || ss[i] > r) return -1;
    if (l <= ss[i] && ee[i] <= r) return seg[i];
    int a = query(i*2,l,r), b = query(i*2+1,l,r);
    if (a == -1) return b;
    if (b == -1) return a;
    return lca(a,b);
}

int cover(int a, int l, int r) {
    if (a == l) return depth[query(1,l+1,r-1)];
    if (a == r) return depth[query(1,l,r-2)];
    return depth[lca(query(1,l,a-2),query(1,a+1,r))];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        int pi; cin >> pi;
        parent[0][i] = pi;    
        adj[i].push_back(pi);
        adj[pi].push_back(i);
    }
    dfs(1,-1,0);

    for (int i = 1; i < maxk; i++) {
        for (int j = 1; j <= n; j++) {
            if (parent[i-1][j] == -1) parent[i][j] = -1;
            else parent[i][j] = parent[i-1][parent[i-1][j]];
        }
    }
    build(1,1,n);
    /*
    for (int i = 1; i <= n; i++) {
        cout << i << ": " << preorder[i] << '\n';
    }
    cout << getmin(1,1,5) << '\n';
    */
    buildLCA(1,1,n-1);
    /*
    for (int i = 1; i <= n; i++) {
        cout << i << ": " << depth[i] << '\n';
    }
    */
    while (q--) {
        int l, r; cin >> l >> r;
        if (l + 1 == r) {
            cout << (depth[l]<depth[r]?l:r) << ' ' << max(depth[l],depth[r]) << '\n';    
        }
        else if (l+2 == r) {
           int r1 = depth[lca(l+1,l+2)];
           int r2 = depth[lca(l,r)];
           int r3 = depth[lca(l,l+1)];
           cout << (r1>max(r2,r3)?l:r2>r3?l+1:l+2) << ' ' << max(r1,max(r2,r3)) << '\n';
        }
        else {
            int a = inv[getmax(1,l,r)];
            int b = inv[getmin(1,l,r)];
            int r1 = cover(a,l,r);
            int r2 = cover(b,l,r);
            cout << (r1>r2?a:b) << ' ' << max(r1,r2) << '\n';
        }
    }
        
    return 0;
}

