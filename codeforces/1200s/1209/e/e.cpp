#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int a[5][105];

int n, m;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                a[i][j] = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
            }
        }
        vector<pair<int,int>> v;
        for (int j = 0; j < m; j++) {
            int mx = 0;
            for (int i = 0; i < n; i++) {
                mx = max(mx,a[i][j]);
            }
            v.push_back({mx,j});
        }
        sort(v.begin(),v.end(),[](auto a, auto b) {
                if (a.first != b.first) return a.first > b.first;
                return a.second < b.second;
                });
        int num = min(4,m);
        vector<int> indices;
        for (int i = 0; i < num; i++) {
            indices.push_back(v[i].second);
        }
        while (indices.size() < 4) indices.push_back(m);
        int res = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    for (int l = 0; l < n; l++) {
                        int ans = 0;
                        for (int r = 0; r < n; r++) {
                            int mx = 0;
                            mx = max(mx,a[(i+r)%n][indices[0]]);
                            mx = max(mx,a[(j+r)%n][indices[1]]);
                            mx = max(mx,a[(k+r)%n][indices[2]]);
                            mx = max(mx,a[(l+r)%n][indices[3]]);
                            ans += mx;
                        }
                        res = max(res,ans);
                    }
                }
            }
        }
        cout << res << '\n';
    }

}

