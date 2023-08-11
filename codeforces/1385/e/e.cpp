#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> dir(n);
        vector<pair<int,int>> undir;
        vector<int> deg(n);
        for (int i = 0; i < m; i++) {
            int t, x, y; cin >> t >> x >> y;
            --x; --y;
            if (t == 0) {
                undir.push_back({x,y});
            }
            else {
                dir[x].push_back(y); 
                ++deg[y];
            }
        }
        vector<int> order(n);
        int pt = 0;
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (!deg[i]) q.push(i); 
        }
        while (!q.empty()) {
            int i = q.front(); q.pop();    
            order[i] = pt++;
            for (int j: dir[i]) {
                if (--deg[j] == 0) {
                    q.push(j);
                }
            }
        }
        if (pt < n) {
            //has loop
            cout << "NO\n";
        }
        else {
            cout << "YES\n";
            for (int i = 0; i < n; i++) {
                for (int j: dir[i]) {
                    cout << i+1 << ' ' << j+1 << '\n';
                }
            }
            for (auto p: undir) {
                if (order[p.first] > order[p.second]) {
                    swap(p.first,p.second);
                }
                cout << p.first+1 << ' ' << p.second+1 << '\n';
            }
        }
    }
}
