#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using ll = long long;
template <class K, class V = __gnu_pbds::null_type>
using ordered_set = __gnu_pbds::tree<K, V, std::greater<K>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

const int maxn = 1e5+5;
int n, q;
int a[maxn];
vector<int> adj[maxn];

int mx_set(const set<pair<int,int>>& s) {
    return s.rbegin()->first;
}

vector<pair<int,int>> fst_queries[maxn], snd_queries[maxn]; //{k,id}
ll sum[maxn];
set<pair<int,int>> mx[maxn];
ordered_set<pair<ll,int>> os_sum;
ordered_set<pair<int,int>> os_mx;
void dfs(int i, int p) {
    sum[i] = a[i];
    mx[i].insert({a[i],i});
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
        sum[i] += sum[j];
        mx[i].insert({mx_set(mx[j]),j});
    }
    os_sum.insert({sum[i],i});
    os_mx.insert({mx_set(mx[i]),i});
}
ll ans[maxn];
void dfs2(int i, int p) {
    /*
    cout << i << "::::\n";
    for (auto p: os_sum) {
        cout << p.second << ": " << p.first << '\n'; 
    }
    */
    for (auto p: fst_queries[i]) {
        int k = p.first;
        int id = p.second;
        ans[id] = os_sum.find_by_order(k-1)->first;
    }
    for (int j: adj[i]) {
        if (j == p) continue;
        ll old_i_sum = sum[i];
        ll old_j_sum = sum[j];

        os_sum.erase({sum[i],i});
        os_sum.erase({sum[j],j});
        sum[i] = old_i_sum-old_j_sum;
        sum[j] = old_j_sum+sum[i];
        os_sum.insert({sum[i],i});
        os_sum.insert({sum[j],j});

        dfs2(j,i);

        os_sum.erase({sum[i],i});
        os_sum.erase({sum[j],j});
        sum[i] = old_i_sum;
        sum[j] = old_j_sum;
        os_sum.insert({sum[i],i});
        os_sum.insert({sum[j],j});
    }
}

void dfs3(int i, int p) {
    for (auto p: snd_queries[i]) {
        int k = p.first;
        int id = p.second;
        ans[id] = os_mx.find_by_order(k-1)->first;
    }
    for (int j: adj[i]) {
        if (j == p) continue;

        int old_i_mx = mx_set(mx[i]);
        int old_j_mx = mx_set(mx[j]);

        os_mx.erase({old_i_mx,i});
        os_mx.erase({old_j_mx,j});
        mx[i].erase({old_j_mx,j});
        mx[j].insert({old_i_mx,i});
        os_mx.insert({mx_set(mx[i]),i});
        os_mx.insert({mx_set(mx[j]),j});

        dfs3(j,i);

        os_mx.erase({mx_set(mx[i]),i});
        os_mx.erase({mx_set(mx[j]),j});
        mx[i].insert({old_j_mx,j});
        mx[j].erase({old_i_mx,i});
        os_mx.insert({mx_set(mx[i]),i});
        os_mx.insert({mx_set(mx[j]),j});
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    bool has2 = false;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < q; i++) {
        int t, r, k; cin >> t >> r >> k;
        if (t == 2) has2 = true;

        if (t == 1) fst_queries[r].push_back({k,i});
        else snd_queries[r].push_back({k,i});
    }
    dfs(1,1);
    dfs2(1,1);
    if (has2) dfs3(1,1);
    //output
    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }
}
