#include <bits/stdc++.h>
using namespace std;
using ll = long long;


//check if alice can immediately win
//if da*2 >= db, then alice should always win
//(can't escape, must go down subtree)
//Otherwise, if Bob can get to a node before alice that has another node that is distance db away, then he can always go back and forth

const int maxn = 1e5+5;
int N;
vector<int> adj[maxn];
int a, b, da, db;
int dista[maxn], distb[maxn];
string solve() {
    cin >> N;
    cin >> a >> b >> da >> db;
    for (int i = 1; i <= N; i++) {
        adj[i].clear();
        dista[i] = distb[i] = -1;
    }
    for (int i = 0; i < N-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    queue<int> q;
    q.push(a);
    dista[a] = 0;
    while (!q.empty()) {
        int i = q.front(); q.pop();
        for (int j: adj[i]) {
            if (dista[j] == -1) {
                dista[j] = dista[i] + 1;
                q.push(j);
            }
        }
    }
    if (dista[b] <= da) {
        return "Alice";
    }
    if (da*2 >= db) {
        return "Alice";
    }
    pair<int,int> farthest = {-1,-1};
    for (int i = 1; i <= N; i++) {
        farthest = max(farthest,make_pair(dista[i],i));
    }
    int rt = farthest.second;
    q.push(rt);
    for (int i = 1; i <= N; i++) dista[i] = -1;
    dista[rt] = 0;
    while (!q.empty()) {
        int i = q.front(); q.pop();
        for (int j: adj[i]) {
            if (dista[j] == -1) {
                dista[j] = dista[i] + 1;
                q.push(j);
            }
        }
    }
    farthest = {-1,-1};
    for (int i = 1; i <= N; i++) {
        farthest = max(farthest,make_pair(dista[i],i));
    }
    int diam = farthest.first;
    if (min(diam,db) > 2*da) {
        return "Bob";
    }
    else {
        return "Alice";
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cout << solve() << '\n';
    }
}

