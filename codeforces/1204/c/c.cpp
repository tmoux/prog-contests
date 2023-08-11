#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int n, m, p[maxm];

const int INF = 1e9+9;
ll dist[maxn][maxn];

const int maxm = 2e6+6;
int previous[maxm];
int d[maxm];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            dist[i][j] = INF;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c; cin >> c;
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = c == '1' ? 1 : INF;
        }
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> p[i];
    }
    //floyd-warshall
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) 
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    /*
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << dist[i][j] << ' ';
        }
        cout << '\n';
    }
    */
    vector<int> ans;
    ans.push_back(p[1]);
    int last = 1;
    for (int i = 2; i <= m; i++) {
        if (dist[p[last]][p[i]] < i-last) {
            ans.push_back(p[i-1]);
            last = i-1;
        }
    }
    ans.push_back(p[m]);
    
    cout << ans.size() << '\n';
    for (int i: ans) {
        cout << i << ' ';
    }
    cout << '\n';
}

