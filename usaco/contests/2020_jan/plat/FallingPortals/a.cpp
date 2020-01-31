#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, y[maxn], q[maxn];

struct Point
{
    ll x, y;
    Point() {}
    Point(ll _x, ll _y) {
        x = _x;
        y = _y;
    }
    Point operator-(Point a) {
        return Point(x-a.x,y-a.y);
    }
};

ll cross(Point a, Point b) {
    return a.x*b.y-a.y*b.x;
}

Point p[maxn];
pair<ll,ll> ans[maxn];

bool operator<(pair<ll,ll> a, pair<ll,ll> b) {
    return a.first*b.second < a.second*b.first;
}

pair<ll,ll> slope(Point a, Point b) {
    int y = abs(a.y-b.y);
    int x = abs(a.x-b.x);
    int gc = __gcd(x,y);
    return {y/gc,x/gc};
}

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("falling.in","r",stdin); freopen("falling.out","w",stdout);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> y[i];
    for (int i = 1; i <= n; i++) cin >> q[i];
    for (int i = 1; i <= n; i++) {
        p[i] = Point(i,y[i]);
    }
    for (int i = 1; i <= n; i++) {
        pair<ll,ll> ans = {2e9,1};
        if (i < q[i] && y[i] < y[q[i]] || i > q[i] && y[i] > y[q[i]]) {
            ans = slope(p[i],p[q[i]]);
        }
        for (int j = 1; j <= n; j++) {
            if (j == i || j == q[i]) continue;
            if (((i > j && y[i] > y[j]) ||
                (i < j && y[i] < y[j])) &&
                ((j < q[i] && y[j] < y[q[i]]) ||
                (j > q[i] && y[j] > y[q[i]]))) {
                if (slope(p[i],p[j]) < slope(p[j],p[q[i]])) {
                    if (slope(p[j],p[q[i]]) < ans)
                        ans = slope(p[j],p[q[i]]);
                }
            }
        }
        if (ans.first == 2e9) {
            cout << -1 << '\n';
        }
        else {
            printf("%d/%d\n",ans.first,ans.second);
        }
    }
    return 0;
    for (int i = 1; i <= n; i++) {
        if (q[i] < i && y[q[i]] < y[i]) {
            pair<ll,ll> ans = slope(p[i],p[q[i]]);
            for (int j = i; j <= n; j++) {
                if (y[j] > y[i]) {
                    pair<ll,ll> tr = slope(p[j],p[q[i]]);
                    if (tr < ans) ans = tr;
                }
            }
            cout << ans.first << '/' << ans.second << '\n';
        }
        else if (q[i] > i && y[q[i]] > y[i]) {
            pair<ll,ll> ans = slope(p[i],p[q[i]]);
            for (int j = i; j >= 1; j--) {
                if (y[j] < y[i]) {
                    pair<ll,ll> tr = slope(p[j],p[q[i]]);
                    if (tr < ans) ans = tr;
                }
            }
            cout << ans.first << '/' << ans.second << '\n';
        }
        else {
            cout << -1 << '\n';
        }
    }
}

