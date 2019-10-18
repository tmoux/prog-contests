#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
 
const ld PI = atan(1)*4;
int N;
struct Point
{
    ll x, y;
    ld angle;
};
vector<Point> pts;
 
Point add(Point a, Point b) {
    return {a.x+b.x,a.y+b.y};
}

Point sub(Point a, Point b) {
    return {a.x-b.x,a.y-b.y};
}
 
ll mag(Point a) {
    return 1LL*a.x*a.x + 1LL*a.y*a.y;
}
 
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) {
        ll xi, yi; cin >> xi >> yi;
        if (xi == 0 && yi == 0) {
            continue;
        }
        else {
            pts.push_back({xi,yi,atan2(xi,yi)});
        }
    }
    N = pts.size();
    sort(pts.begin(),pts.end(),[](Point a, Point b) {
            return a.angle < b.angle;
            });
    for (int i = 0; i < N; i++) {
        pts.push_back({pts[i].x,pts[i].y,pts[i].angle+2*PI});
    }
    
    ll res = 0;
    Point sum = {0,0};
    int j = 0;
    for (int i = 0; i < N; i++) {
        if (i > 0) {
            sum = sub(sum,pts[i-1]);
        }
        res = max(res,mag(sum));
        while (j < pts.size() && pts[j].angle < pts[i].angle + PI) {
            sum = add(sum,pts[j]);
            res = max(res,mag(sum));
            j++;
        }
        res = max(res,mag(sum));
    }
    cout << res << '\n';
}
