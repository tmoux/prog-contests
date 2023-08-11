#include <iostream>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, M;
struct Edge { int to, digit; };
vector<Edge> adj[maxn];
bool vis[maxn];
int sub_size[maxn];
ll expt[maxn], inverse[maxn];

int modInverse(int a, int m)
{
    int m0 = m;
    int y = 0, x = 1;
 
    if (m == 1)
      return 0;
 
    while (a > 1)
    {
        // q is quotient
        int q = a / m;
        int t = m;
 
        // m is remainder now, process same as
        // Euclid's algo
        m = a % m, a = t;
        t = y;
 
        // Update y and x
        y = x - q * y;
        x = t;
    }
 
    // Make x positive
    if (x < 0)
       x += m0;
 
    return x;
}

int dfs_size(int i, int par) {
    sub_size[i] = 1;
    for (Edge e: adj[i]) {
        if (!vis[e.to] && e.to != par) {
            sub_size[i] += dfs_size(e.to,i);
        }
    }
    return sub_size[i];
}

int get_centroid(int i, int par, int compSize) {
    for (Edge e: adj[i]) {
        if (!vis[e.to] && e.to != par && sub_size[e.to] * 2 > compSize) {
            return get_centroid(e.to,i,compSize);
        }
    }
    return i;
}

struct Path { ll sum; int len; };
void solve_dfs(int i, int par, vector<Path>& away, vector<Path>& from, ll curr1, ll curr2, int len) {
    for (Edge e: adj[i]) {
        if (!vis[e.to] && e.to != par) {
            ll p1 = (curr1 * 10 + e.digit) % M;
            away.push_back({p1,len+1});
            ll p2 = (expt[len] * e.digit + curr2) % M;
            from.push_back({p2,len+1});
            solve_dfs(e.to,i,away,from,p1,p2,len+1);
        }
    }
}

ll solve_tree(int centroid) {
    map<ll,int> orAway, orFrom;
    orAway[0]++;
    orFrom[0]++;
    ll res = 0;
    for (Edge e: adj[centroid]) {
        if (!vis[e.to]) {
            vector<Path> away, from;
            away.push_back({e.digit % M, 1});
            from.push_back({e.digit % M, 1});
            solve_dfs(e.to,centroid,away,from,e.digit,e.digit,1);
            
            for (Path p: away) {
                ll desired = ((M-p.sum) * inverse[p.len]) % M;
                if (orFrom.count(desired)) {
                    res += orFrom[desired];
                }
            }
            for (Path p: from) {
                ll desired = p.sum; 
                if (orAway.count(desired)) {
                    res += orAway[desired];
                }
            }

            for (Path p: away) {
                ll change = (M - ((p.sum * inverse[p.len]) % M)) % M;
                orAway[change]++;
            }
            for (Path p: from) {
                orFrom[p.sum]++;
            }
        }
    }
    return res;
}

ll decomp(int i) {
    int compSize = dfs_size(i,i);
    int centroid = get_centroid(i,i,compSize);
    vis[centroid] = true;
    ll res = solve_tree(centroid);
    for (Edge e: adj[centroid]) {
        if (!vis[e.to]) {
            res += decomp(e.to);
        }
    }
    return res;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> M;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    //precomp exponents and inverses
    ll mult = 1;
    for (int i = 0; i <= n + 1; i++) {
        expt[i] = mult;
        mult = (mult * 10) % M;
    }
    inverse[0] = 1;
    inverse[1] = modInverse(10,M);
    for (int i = 2; i <= n + 1; i++) {
        inverse[i] = (inverse[i-1] * inverse[1]) % M;
    }

    //centroid decomposition
    ll ans = decomp(0);
    cout << ans << '\n';

    return 0;
}
	

