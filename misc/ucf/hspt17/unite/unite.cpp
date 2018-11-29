#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 505;
int n;
bool used[maxn];
int dist[maxn][maxn];
int x[maxn], y[maxn], z[maxn];

int sq(int x) { return x*x;}

void solve(int t) {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i] >> z[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = sq(x[i]-x[j]) + sq(y[i]-y[j]) + sq(z[i]-z[j]);
        }
    }
    memset(used,0,sizeof used);
    int cost = 0;
    used[0] = true;
    vector<int> d(n);
    for (int i = 0; i < n; i++) d[i] = dist[0][i];
    for (int i = 0; i < n - 1; i++) {
        int mindist = 987654321, idx;
        for (int j = 0; j < n; j++) {
            if (!used[j]) {
                if (d[j] < mindist) {
                    mindist = d[j];
                    idx = j;
                }
            }
        }
        used[idx] = true;
        cost += mindist;
        for (int j = 0; j < n; j++) {
            d[j] = min(d[j],dist[j][idx]);
        }
    }
    printf("Universe #%d: %d\n",t,cost);
}

int main()
{
    int t; cin >> t;
    for (int i = 1; i <= t; i++) solve(i);

    return 0;
}

