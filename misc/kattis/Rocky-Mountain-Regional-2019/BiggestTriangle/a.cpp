#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

ld eps = 1e-8;

struct Point
{
    ld x, y;
    bool operator==(const Point& rhs) {
        return x == rhs.x && y == rhs.y;
    }
};

ld dist(Point a, Point b) {
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

ld inf = 1e30;
Point bad = {inf,inf};

struct Line
{
    ld m, b;
    Line(ld _m, ld _b) {
        m = _m;
        b = _b;
    }
    Line(int x1, int y1, int x2, int y2) {
        m = x1-x2==0?inf:(ld)(y2-y1)/(ld)(x2-x1);
        b = x1-x2==0?x1:y1-m*x1;        
    }
    ld eval(ld x) {
        return x*m+b;
    }
};

Point intersect(Line l1, Line l2) {
    if (l1.m == l2.m) return bad;
    if (l1.m == inf) {
        return {l1.b,l2.eval(l1.b)};
    }
    else if (l2.m == inf) {
        return {l2.b,l1.eval(l2.b)};
    }
    else {
        ld x = (l2.b-l1.b)/(l1.m-l2.m);
        return {x,l1.eval(x)};
    }
}

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<Line> v;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        v.push_back(Line(x1,y1,x2,y2));
    }
    ld ans = 0;
    /*
    for (int i = 0; i < n; i++) 
        cout << i << ": " << v[i].m << ' ' << v[i].b << '\n';
        */
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            for (int k = j+1; k < n; k++) {
                Point p1 = intersect(v[i],v[j]);
                Point p2 = intersect(v[j],v[k]);
                Point p3 = intersect(v[i],v[k]);
                if (p1 == bad || p2 == bad || p3 == bad) continue;
                ld perim = dist(p1,p2)+dist(p2,p3)+dist(p3,p1);
                ans = max(ans,perim);
                /*
                cout << i << ' ' << j << ' ' << k << ": " << perim << '\n';
                cout << p1.x << ' ' << p1.y << '\n';
                cout << p2.x << ' ' << p2.y << '\n';
                cout << p3.x << ' ' << p3.y << '\n';
                */
            }
        }
    }
    if (ans < eps) {
        cout << "no triangle\n";
    }
    else {
        cout << fixed << setprecision(20) << ans << '\n';
    }
}

