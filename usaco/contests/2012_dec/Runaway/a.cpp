#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using ll = long long;

template <class K, class V = __gnu_pbds::null_type>
using ordered_multiset = __gnu_pbds::tree<K, V, std::less_equal<K>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

const int maxn = 2e5+5;
int N;
ll L;
struct Edge
{
    int to;
    ll weight;
    Edge(int a, ll b) {
        to = a;
        weight = b;
    }
};
vector<Edge> adj[maxn];
int sub_size[maxn], ans[maxn], bigChild[maxn];

int dfs(int i) {
    pair<int,int> best = {-1,-1};
    sub_size[i] = 1;
    for (Edge e: adj[i]) {
        sub_size[i] += dfs(e.to); 
        best = max(best,{sub_size[e.to],e.to});    
    }
    bigChild[i] = best.second;
    return sub_size[i];
}

struct Node
{
    ordered_multiset<ll> v;
    ll delta = 0;
    Node() {}
    void insert(ll x) {
        v.insert(x-delta);
    }
    ll extract(ll x) {
        return x + delta;
    }
    void addEdge(ll e) {
        delta += e;
    }
};

Node* dfs2(int i) {
    Node *ni = NULL;
    for (Edge e: adj[i]) {
        if (e.to == bigChild[i]) {
            ni = dfs2(e.to);
            ni->addEdge(e.weight);
            ni->insert(0);
            break;
        }
    }
    if (ni == NULL) {
        ni = new Node();
        ni->insert(0);
    }
    for (Edge e: adj[i]) {
        if (e.to == bigChild[i]) continue;
        Node *nj = dfs2(e.to);
        nj->addEdge(e.weight);
        for (ll x: nj->v) {
            ll xv = nj->extract(x);
            ni->insert(xv);                                           
        }
    }
    int an = ni->v.order_of_key(L - ni->delta + 1);
    ans[i] = an;
    return ni;
}

int main()
{
    freopen("runaway.in","r",stdin); freopen("runaway.out","w",stdout);
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> L;
    for (int i = 2; i <= N; i++) {
        int p; ll l; cin >> p >> l;
        adj[p].push_back(Edge(i,l));
    }
    dfs(1);
    dfs2(1);
    for (int i = 1; i <= N; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}

