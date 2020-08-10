#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//Actually we just need to remove all even cycles, then the remaining graph is a set of cactuses, which all have (< 3n/2) edges

const int maxn = 3e5+5;
int N, M;

vector<int> adj[maxn];
int ans[maxn];
bool vis[maxn];
int depth[maxn];
map<pair<int,int>,int> mp;

vector<int> st;

void merge(set<int>& ni, set<int>& nj) {
    if (ni.size() < nj.size()) swap(ni,nj);
    for (auto j: nj) ni.insert(j);
}

set<int>* dfs(int i, int p, int d, int last) {
    vis[i] = true;
    depth[i] = d;    
    st.push_back(i);
    set<int>* ni = new set<int>;
    ni->insert(0);
    for (int j: adj[i]) {
        if (j == p) continue;
        if (vis[j] && (depth[i]-depth[j])%2==1 && depth[j] >= last) {
            //even cycle
            for (int idx = st.size()-1, x = 0; idx >= 0; idx--, x ^= 1) {
                int color = x ? -1 : 1;
                if (st[idx] == i) ans[mp[make_pair(i,j)]] = color;
                else {
                    ans[mp[make_pair(st[idx],st[idx+1])]] = color;
                }
                if (st[idx] == j) break;
            }
            last = depth[i];
            ni->insert(depth[j]);
            break;
        }
    }
    for (int j: adj[i]) {
        if (!vis[j]) {
            auto nj = dfs(j,i,d+1,last);
            auto it = nj->lower_bound(depth[i]);
            if (last != depth[i] && it != nj->begin()) last = depth[i];
            merge(*ni,*nj);
        }
    }
    st.pop_back();
    /*
    cout << i << "::: ";
    for (auto j: (*ni)) {
        cout << j << ' ';
    }
    cout << '\n';
    */
    return ni;
}

random_device device;
mt19937 gen(device());

void solve() {
    cin >> N >> M;
    mp.clear();
    st.clear();
    for (int i = 1; i <= N; i++) {
        adj[i].clear();
        vis[i] = false;
        depth[i] = 0;
    }
    vector<pair<int,int>> edges(M);
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        edges[i] = {a,b};
        ans[i] = 0;
        adj[a].push_back(b);
        adj[b].push_back(a);
        mp[make_pair(a,b)] = i;
        mp[make_pair(b,a)] = i;
    }
    for (int i = 1; i <= N; i++) shuffle(adj[i].begin(),adj[i].end(),gen);
    for (int i = 1; i <= N; i++) {
       if (vis[i]) continue; 
       st.clear();
       dfs(i,i,0,0);
    }

    //sanity checks
    vector<int> v(N+1,0);
    int yellow = 0;
    for (int i = 0; i < M; i++) {
        v[edges[i].first] += ans[i];
        v[edges[i].second] += ans[i];
        if (!ans[i]) ++yellow;
    }
    for (int i = 1; i <= N; i++) {
        //cout << i << ": " << v[i] << endl;
        assert(v[i] == 0);
    }
    double R = ((double)(yellow)/N);
    cout << "R = " << R << endl;
    cout << yellow << ' ' << N << endl;
    for (int i = 0; i < M; i++) {
        if (ans[i] == 0) cout << edges[i].first << ' ' << edges[i].second << endl;
    }
    //assert(R < 3);
    /*
    //output
    for (int i = 0; i < M; i++) {
        cout << ans[i] << '\n';
    }
    */
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}
