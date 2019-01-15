#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, T;
struct Line
{
    int x1, x2, y1, y2, t;
};

int main()
{
    freopen("mowing.in","r",stdin); freopen("mowing.out","w",stdout);
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> T;
    vector<Line> horiz, verts;
    int xp, yp; cin >> xp >> yp;
    for (int i = 2; i <= N; i++) {
        int x, y; cin >> x >> y;
        if (x == xp) {
            //vertical
            verts.push_back({x,x,min(y,yp),max(y,yp),i});
        }
        else {
            //horizontal
            horiz.push_back({min(x,xp),max(x,xp),y,y,i});
        }
        xp = x;
        yp = y;
    }
    ll res = 0;
    for (Line v: verts) {
        for (Line h: horiz) {
            if (h.x1 < v.x1 && v.x1 < h.x2 && v.y1 < h.y1 && h.y1 < v.y2 && (h.t < v.t-T || h.t > v.t+T)) res++;
        }
    }
    cout << res << '\n';
    return 0;
}
