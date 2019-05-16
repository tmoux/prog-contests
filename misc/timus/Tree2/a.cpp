#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 20005;
int n, q;
vector<int> adj[maxn];
vector<pair<int,int>> queries[50005]; //dist, id
int ans[50005];

bool blocked[maxn];
int sub_size[maxn];

int dfsSize(int i, int p) {
    sub_size[i] = 1;
    for (int j: adj[i]) {
        if (j == p || blocked[j]) continue;
        sub_size[i] += dfsSize(j,i);
    }
    return sub_size[i];
}
int getCentroid(int i, int p, int compSize) {
    for (int j: adj[i]) {
        if (j == p || blocked[j]) continue;
        if (sub_size[j] * 2 > compSize) return getCentroid(j,i,compSize);
    }
    return i;
}

void add(int i, int p, int d, map<int,int>& dist) {
    dist[i] = d;
    for (int j: adj[i]) {
        if (blocked[j] || j == p) continue;
        add(j,i,d+1,dist);
    }
}

void solve(int centroid) {
    map<int,int> dist; //maps dist to a node
    dist[0] = centroid;
    for (int j: adj[centroid]) {
        if (blocked[j]) continue;
        map<int,int> curr;
        add(j,j,1,curr);
        for (auto q: curr) {
            int i = q.first;
            int d = q.second;
            //cout << i << ": " << d << '\n';
            for (auto p: queries[i]) {
                if (dist.count(p.first - d)) {
                    ans[p.second] = dist[p.first-d];
                }
            }
        }
        for (auto q: curr) {
            //add to dist
            if (!dist.count(q.second)) dist[q.second] = q.first;    
        }
    }
    dist.clear();
    dist[0] = centroid;
    reverse(adj[centroid].begin(),adj[centroid].end());
    for (int j: adj[centroid]) {
        if (blocked[j]) continue;
        map<int,int> curr;
        add(j,j,1,curr);
        for (auto q: curr) {
            int i = q.first;
            int d = q.second;
            for (auto p: queries[i]) {
                if (dist.count(p.first - d)) {
                    ans[p.second] = dist[p.first-d];
                }
            }
        }
        for (auto q: curr) {
            //add to dist
            if (!dist.count(q.second)) dist[q.second] = q.first;    
        }
    }
    for (auto p: queries[centroid]) {
        if (dist.count(p.first)) {
            ans[p.second] = dist[p.first];
        }
    }
}

void decomp(int i) {
    int compSize = dfsSize(i,i);
    int centroid = getCentroid(i,i,compSize);
    blocked[centroid] = true;
    //cout << "centroid = " << centroid << '\n';
    solve(centroid);
    for (int j: adj[centroid]) {
        if (blocked[j]) continue;
        decomp(j);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < q; i++) {
        int v, d; cin >> v >> d;
        queries[v].push_back({d,i+1});
    }
    decomp(1);

    for (int i = 1; i <= q; i++) {
        cout << ans[i] << '\n';
    }
}

