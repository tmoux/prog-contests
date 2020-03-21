#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    int n; cin >> n;
    vector<vector<int>> adj(n);
    vector<int> deg(n);
    vector<int> ans(n,-1);
    map<pair<int,int>,int> mp;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        ++deg[a]; ++deg[b];
        mp[make_pair(a,b)] = i;
        mp[make_pair(b,a)] = i;
    }
    for (int i = 0; i < n; i++) {
        if (deg[i] >= 3) {
            for (int j = 0; j < 3; j++) {
                ans[mp[make_pair(i,adj[i][j])]] = j;
            }
            int pt = 3;
            for (int j = 0; j < n-1; j++) {
                if (ans[j] == -1) {
                    ans[j] = pt++;
                }
                cout << ans[j] << '\n';
            }
            return 0;
        }
    }
    for (int j = 0; j < n-1; j++) {
        cout << j << '\n';
    }
}
