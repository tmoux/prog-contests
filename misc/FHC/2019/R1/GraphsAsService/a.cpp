#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 55, INF = 1e9+9;
int dist[maxn][maxn];
int N, M;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cout << "Case #" << qq << ": ";
        cin >> N >> M;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                dist[i][j] = INF;
            }
        }
        vector<vector<int>> cs;
        while (M--) {
            int x, y, z;
            cin >> x >> y >> z;
            dist[x][y] = dist[y][x] = z;
            cs.push_back({x,y,z});
        }
        for (int k = 1; k <= N; k++) {
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        /*
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                cout << dist[i][j] << ' ';
            }
            cout << '\n';
        }
        */
        
        bool poss = true;
        for (auto v: cs) {
            if (dist[v[0]][v[1]] != v[2]) {
                poss = false;
                break;
            }
        }
        if (!poss) {
            cout << "Impossible\n";
        }
        else {
            vector<vector<int>> ans;
            for (int i = 1; i <= N; i++) {
                for (int j = i + 1; j <= N; j++) {
                    if (dist[i][j] <= 1000000) {
                        ans.push_back({i,j,dist[i][j]});    
                    }
                }
            }
            //output
            cout << ans.size() << '\n';
            for (auto v: ans) {
                cout << v[0] << ' ' << v[1] << ' ' << v[2] << '\n';
            }
        }
    }
}

