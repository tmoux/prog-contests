#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
const int blk = 450;
int n, q;
int a[maxn], b[maxn];
int tin[maxn], tout[maxn];
vector<int> adj[maxn];
int pt = 0;
void dfs(int i) {
    tin[i] = pt++;
    a[tin[i]] = b[i];
    for (int j: adj[i]) {
        dfs(j);
    }
    tout[i] = pt-1;
}

int bucket[maxn];
int sum[maxn], flip[maxn], sz[maxn];

int SUM(int l, int r) {
    int res = 0;
    while (l != 0 && bucket[l] == bucket[l-1] && l <= r) {
        res += flip[bucket[l]] ? 1-a[l] : a[l];
        l++;
    }
    while (bucket[l] != bucket[r] && l <= r) {
        res += flip[bucket[l]] ? sz[bucket[l]] - sum[bucket[l]] : sum[bucket[l]];      
        l += blk;
    }
    while (l <= r) {
        res += flip[bucket[l]] ? 1-a[l] : a[l];
        l++;
    }
    return res;
}

void FLIP(int l, int r) {
    while (l != 0 && bucket[l] == bucket[l-1] && l <= r) {
        if (a[l] == 0) {
            a[l] = 1;
            sum[bucket[l]]++;
        }
        else {
            a[l] = 0;
            sum[bucket[l]]--;
        }
        l++;
    }
    while (bucket[l] != bucket[r] && l <= r) {
        flip[bucket[l]] ^= 1;
        l += blk;
    }
    while (l <= r) {
        if (a[l] == 0) {
            a[l] = 1;
            sum[bucket[l]]++;
        }
        else {
            a[l] = 0;
            sum[bucket[l]]--;
        }
        l++;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int pi; cin >> pi;
        adj[pi].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    dfs(1);
    /*
    for (int i = 0; i < n; i++) {
        cout << i << ": " << a[i] << '\n';
    }
    */
    //sqrt decomp
    for (int i = 0; i < n; i++) {
        bucket[i] = i/blk;
        if (a[i] == 1) sum[bucket[i]]++;
        sz[bucket[i]]++;
    }
    cin >> q;
    while (q--) {
        string s; cin >> s;
        int v; cin >> v;
        if (s == "get") {
            //cout << tin[v] << ' ' << tout[v] << '\n';
            int ans = SUM(tin[v],tout[v]);
            cout << ans << '\n';
        }
        else if (s == "pow") {
            FLIP(tin[v],tout[v]);
        }
    }
}

