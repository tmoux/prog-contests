#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m;
multiset<int> adj[maxn];
int w[maxn];
bool used[maxn];

map<pair<int,int>,vector<int>> mp;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        --x; --y;
        mp[make_pair(min(x,y),max(x,y))].push_back(i);
        adj[x].insert(y);
        adj[y].insert(x);
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (w[i] >= adj[i].size()) {
            used[i] = true;
            q.push(i);
        }
    }
    vector<int> ans; 
    while (!q.empty()) {
        int i = q.front(); q.pop();
        //cout << "visiting " << i << endl;
        for (int j: adj[i]) {
            auto p = make_pair(min(i,j),max(i,j));
            int id = mp[p].back(); mp[p].pop_back();
            ans.push_back(id);
            /*
            if (adj[i].count(j)) {
                auto it = adj[i].find(j);
                adj[i].erase(it);
            }
            */
            if (adj[j].count(i)) {
                auto it = adj[j].find(i);
                adj[j].erase(it);
            }
            //cout << j << ": " << adj[j].size() << '\n';
            if (!used[j] && w[j] >= adj[j].size()) {
                used[j] = true;
                q.push(j);
            }
        }
    }
    if (ans.size() == m) {
        cout << "ALIVE\n";
        reverse(ans.begin(),ans.end());
        for (int i: ans) {
            cout << i+1 << ' ';
        }
        cout << '\n';
    }
    else {
        cout << "DEAD\n";
    }
}
