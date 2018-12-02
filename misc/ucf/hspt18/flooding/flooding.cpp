#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point
{
    int x, y;
    Point operator-(const Point& rhs) {
        return {x-rhs.x,y-rhs.y};
    }
};

Point a, b, c;

int cross(Point a, Point b) {
    return a.x*b.y-a.y*b.x;
}

bool inside(Point q) {
    return cross((b-a),(b-q)) > 0 && cross((c-b),(c-q)) > 0 && cross((a-c),(a-q)) > 0;    
}

int main()
{
    int t; cin >> t;
    for (int ww = 1; ww <= t; ww++) {
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
        int ans = 0;
        int n; cin >> n;
        while (n--) {
            Point s, e;
            cin >> s.x >> s.y >> e.x >> e.y;
            bool c1 = inside(s);
            bool c2 = inside(e);
            if (c1 ^ c2) ans++;
        }
        printf("Scenario %d: %d\n",ww,ans);
        //cout << cross((b-a),(b-s)) << ' ' << cross((c-b),(c-s)) << ' ' << cross((a-c),(a-s)) << '\n';
    }

    return 0;
}

