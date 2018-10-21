#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n, depth[maxn], a[maxn], rev[maxn];
vector<int> adj[maxn];
bool vis[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        rev[a[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(),adj[i].end(),[](int l, int r) {
                return rev[l] < rev[r];
                });
    }
    queue<int> q;
    q.push(1);
    vector<int> ans;
    while (!q.empty()) {
        int f = q.front();
        ans.push_back(f);
        vis[f] = true;
        for (int i: adj[f]) {
            if (!vis[i]) {
                q.push(i);
            }
        }
        q.pop();
    }

    //compare ans and a
    for (int i = 0; i < n; i++) {
        if (ans[i] != a[i]) {
            cout << "No" << '\n';
            return 0;
        }
    }
    cout << "Yes" << '\n';
    
    return 0;
}

