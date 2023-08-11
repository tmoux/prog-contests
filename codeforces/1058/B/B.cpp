#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point
{
    int x, y;
    Point operator-(const Point& r) {
        return {x-r.x,y-r.y};
    }
    Point operator+(const Point& r) {
        return {x+r.x,y+r.y};
    }
};
int cross(Point a, Point b) {
    return a.x*b.y - a.y*b.x;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, d; cin >> n >> d;
    Point l[4] = {{d,0}, {n,n-d}, {n-d,n}, {0,d}};
    int m; cin >> m;
    while (m--) {
        int x, y; cin >> x >> y;
        Point p = {x,y};
        bool is = true;
        for (int i = 0; i < 4; i++) {
            Point a = l[i]-l[(i+3)%4];
            Point b = p-l[i];
            int c = cross(a,b);
            //cout << a.x << ' ' << a.y << '\n';
            //cout << b.x << ' ' << b.y << '\n';
            //cout << c << '\n';
            if (c < 0) {
                is = false;
                break;
            }
        }
        cout << (is ? "YES" : "NO") << '\n';
    }

    return 0;
}

