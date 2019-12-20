#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int maxn = 1e5+505;
int n, q;
vector<int> adj[maxn];
const int blk = 500;

int bucket[maxn];
gp_hash_table<int, int> colors[maxn];
int ind_sum[maxn];
struct Block
{
    int sz = 0;
    vector<int> cnt; //how many inside block are colored c
    vector<int> lazy; //list of colors need to send to whole block
    int sum = 0; //total sum of colorfulness
} blocks[maxn];
int start[maxn];

int pt = 0;
int tin[maxn], tout[maxn];

void dfs(int i, int p) {
    tin[i] = pt++;
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
    }
    tout[i] = pt-1;
}

void refresh(int b) { //applies lazy update
    if (blocks[b].lazy.empty()) return;
    for (int c: blocks[b].lazy) {
        for (int i = start[b]; bucket[i] == b; i++) {
            if (colors[i].find(c) == colors[i].end()) {
                ind_sum[i]++;
            }
            else {
                colors[i].erase(c);
            }
        }
    }
    blocks[b].lazy.clear();
}

void UPD(int l, int r, int c) {
    refresh(bucket[l]);
    while (l != 0 && bucket[l] == bucket[l-1] && l <= r) {
        if (colors[l].find(c) == colors[l].end() && blocks[bucket[l]].cnt[c] < blocks[bucket[l]].sz) {
            colors[l][c] = 1;
            ind_sum[l]++;
            blocks[bucket[l]].sum++;
            blocks[bucket[l]].cnt[c]++;
        }
        l++;
    }
    while (bucket[l] < bucket[r] && l <= r) {
        if (blocks[bucket[l]].cnt[c] < blocks[bucket[l]].sz) {
            blocks[bucket[l]].lazy.push_back(c);
            blocks[bucket[l]].sum += blocks[bucket[l]].sz-blocks[bucket[l]].cnt[c];
            blocks[bucket[l]].cnt[c] = blocks[bucket[l]].sz;
        }
        l += blk;
    }
    refresh(bucket[r]);
    while (l <= r) {
        if (colors[l].find(c) == colors[l].end() && blocks[bucket[l]].cnt[c] < blocks[bucket[l]].sz) {
            colors[l][c] = 1;
            ind_sum[l]++;
            blocks[bucket[l]].sum++;
            blocks[bucket[l]].cnt[c]++;
        }
        l++;
    }
}

ll QUERY(int l, int r) {
    ll res = 0;
    refresh(bucket[l]);
    while (l != 0 && bucket[l] == bucket[l-1] && l <= r) {
        res += ind_sum[l]; 
        //printf("%d: adding %d\n",l,ind_sum[l]);
        l++;
    }
    while (bucket[l] < bucket[r] && l <= r) {
        //printf("block %d: adding %d\n",bucket[l],blocks[bucket[l]].sum);
        res += blocks[bucket[l]].sum;
        l += blk;
    }
    refresh(bucket[r]);
    while (l <= r) {
        res += ind_sum[l];
        //printf("%d: adding %d\n",l,ind_sum[l]);
        l++;
    }
    return res;
}

int main() {
    freopen("snowcow.in","r",stdin); freopen("snowcow.out","w",stdout);
    cin >> n >> q;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,1);
    //sqrt decomposition
    memset(bucket,-1,sizeof bucket);
    for (int i = 0; i < n; i++) {
        bucket[i] = i/blk;
        blocks[bucket[i]].sz++;
        if (i == 0 || bucket[i] != bucket[i-1]) {
            start[bucket[i]] = i;
        }
    }
    for (int i = 0; i <= bucket[n-1]; i++) {
        blocks[i].cnt = vector<int>(100005,0);
    }
    
    while (q--) {
        int t, x; cin >> t >> x;
        if (t == 1) {
            int c; cin >> c;
            //update [tin[x],tout[x]] with color c
            UPD(tin[x],tout[x],c);
        }
        else if (t == 2) {
            //query [tin[x],tout[x]]
            ll ans = QUERY(tin[x],tout[x]);
            cout << ans << '\n';
        }
    }
    //cout << QUERY(tin[3],tout[3]) << '\n';
}
