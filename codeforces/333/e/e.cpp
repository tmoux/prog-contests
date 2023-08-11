#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3005;
int n, x[maxn], y[maxn];
int good[maxn][111];

int dist[maxn][maxn];
int d(int i, int j) {
    return (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << fixed << setprecision(10);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    vector<pair<int,pair<int,int>>> v;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            dist[i][j] = dist[j][i] = d(i,j);
            v.push_back({dist[i][j],{i,j}});
        }
    }
    sort(v.begin(),v.end());
    reverse(v.begin(),v.end());
    for (auto p: v) {
        int ii = p.second.first;
        int jj = p.second.second;
        good[ii][jj/30] |= (1<<(jj%30));
        good[jj][ii/30] |= (1<<(ii%30));
        for (int i = 0; i <= 101; i++) {
            if (good[ii][i] & good[jj][i]) {
                cout << sqrt(p.first)/2.0 << '\n';
                return 0;
            }
        }
    }
}

