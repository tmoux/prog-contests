#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int n;
struct Point
{
    int x, y, id;
} pts[maxn];

ll sqr(int x) {
    return 1LL*x*x;
}

ll dist(Point a, Point b) {
    return sqr(a.x-b.x) + sqr(a.y-b.y);
}

vector<int> adj[maxn];
int color[maxn];

bool poss = true;

void dfs(int i, int c) {
    color[i] = c;
    for (int j: adj[i]) {
        if (color[j] == color[i]) {
            poss = false;
        }
        if (color[j] == -1) {
            dfs(j,1-c);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].id = i+1;
    }
    ll mn = 1LL<<60;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            ll d = dist(pts[i],pts[j]);
            ll mult = 1;
            while (d % 2 == 0) {
                mult *= 2;
                d /= 2;
            }
            mn = min(mn,mult);
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            ll d = dist(pts[i],pts[j])/mn;
            if (d&1) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    memset(color,-1,sizeof color);
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) dfs(i,0);
    }
    //output
    assert(poss);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) ans++;
    }
    cout << ans << '\n';
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) cout << i+1 << ' ';
    }
    cout << '\n';
}

