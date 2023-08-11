#include <bits/stdc++.h>
using namespace std;
using ll = long long;

pair<int,int> ask(vector<int> v) {
    cout << "? " << v.size() << ' ';
    for (auto i: v) {
        cout << i << ' ';
    }
    cout << endl;
    int x, d; cin >> x >> d;
    assert(x != -1);
    return make_pair(x,d);
}

void answer(int a, int b) {
    cout << "! " << a << ' ' << b << endl;
    string s; cin >> s;
    assert(s == "Correct");
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n+1);
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> v;
    for (int i = 1; i <= n; i++) {
        v.push_back(i);
    }
    pair<int,int> ans = ask(v);
    int d = ans.second;
    int x = ans.first;
    vector<int> dist(n+1,n+5);
    vector<int> par(n+1,x);
    queue<int> q;
    dist[x] = 0;
    q.push(x);
    while (!q.empty()) {
        int f = q.front(); q.pop();
        for (auto j: adj[f]) {
            if (dist[j] > dist[f] + 1) {
                dist[j] = dist[f] + 1;
                par[j] = f;
                q.push(j);
            }
        }
    }

    int l1 = x;
    int dd = 0;
    int lo = d/2-1, hi = n+1;
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        vector<int> query;
        for (int j = 1; j <= n; j++) {
            if (dist[j] == mid) query.push_back(j);
        }
        if (query.empty()) {
            hi = mid;
            continue;
        }
        //cout << "dd = " << d << endl;
        auto p = ask(query);
        if (p.second > d) {
            hi = mid;
        }
        else {
            lo = mid;
            l1 = p.first;
        }
    }
    vector<int> used(n+1,false);
    int i = l1;
    do {
        used[i] = true;
        i = par[i];
    } while (i != x);
    vector<int> query;
    int l2;
    if (d-dist[l1] == 0) l2 = x;
    else {
        for (int j = 1; j <= n; j++) {
            if (dist[j] == d-dist[l1] && !used[j]) query.push_back(j);
        }
        auto p = ask(query);
        l2 = p.first;
    }
    answer(l1,l2);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
