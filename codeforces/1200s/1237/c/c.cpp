#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 50005;
int n;
struct Point
{
    ll x, y, z;
} pts[maxn];

bool use[maxn];

ll sqr(ll x) {
    return x*x;
}

ll dist(Point a, Point b) {
    return sqr(a.x-b.x) + sqr(a.y-b.y) + sqr(a.z-b.z);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> pts[i].x >> pts[i].y >> pts[i].z;
    }
    for (int i = 1; i <= n; i++) {
        if (use[i]) continue;
        pair<ll,int> best = {1e18,-1};
        for (int j = i+1; j <= n; j++) {
            if (use[j]) continue;
            best = min(best,{dist(pts[i],pts[j]),j});
        }
        assert(best.second != -1);
        use[i] = true;
        use[best.second] = true;
        cout << i << ' ' << best.second << '\n';
    }
}

