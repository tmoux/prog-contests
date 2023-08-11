#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5+5;
int n, m;
struct Point { 
    int x, y, id; 
    bool operator<(const Point& rhs) {
        return (x-y) < (rhs.x-rhs.y);
    }
};

Point pts[maxn], id[maxn];
ll pfx[maxn], pfy[maxn];

inline ll eval(Point& a, Point& b) {
    return min(a.x+b.y,a.y+b.x);
}

ll ans[maxn];
int main()
{
    scanf("%d %d",&n,&m);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d",&pts[i].x,&pts[i].y);
        pts[i].id = i;
        id[i] = pts[i];
    }
    sort(pts+1,pts+n+1);
    for (int i = 1; i <= n; i++) {
        pfx[i] = pfx[i-1] + pts[i].x;
        pfy[i] = pfy[i-1] + pts[i].y;
    }
    for (int i = 1; i <= n; i++) {
        ans[pts[i].id] += 1LL*(i-1)*pts[i].y+(pfx[i-1]);
        ans[pts[i].id] += 1LL*(n-i)*pts[i].x+(pfy[n]-pfy[i]);
    }
    for (int i = 0; i < m; i++) {
        int a, b; scanf("%d %d",&a,&b);
        ll r = eval(id[a],id[b]);
        ans[a] -= r;
        ans[b] -= r;
    }
    //output
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }


    return 0;
}

