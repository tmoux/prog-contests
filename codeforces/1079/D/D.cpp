#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

double a, b, c;
struct Point
{
    double x, y;
};

vector<Point> intersection(Point p) {
    if (a == 0) {
        return {{p.x,c/b}};
    }
    else if (b == 0) {
        return {{c/a,p.y}};
    }
    Point p1 = {p.x,(-c-a*p.x)/b};
    Point p2 = {(-c-b*p.y)/a,p.y};
    return {p1,p2};
}
double dist(Point a, Point b) {
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> a >> b >> c;
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    Point A = {x1,y1};
    Point B = {x2,y2};
    double ans = (abs(A.x-B.x) + abs(A.y-B.y));
    auto p1 = intersection(A);
    auto p2 = intersection(B);
    for (Point q: p1) {
        for (Point w: p2) {
            double d = dist(A,q) + dist(B,w) + dist(q,w);
            ans = min(ans,d);
        }
    }
    cout << fixed << setprecision(10) << ans << '\n';

    return 0;
}

