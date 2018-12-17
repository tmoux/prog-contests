#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int R;
struct Point {
    int x, y, mass;
    bool operator<(Point& r) const {
        return mass < r.mass;
    }
};

double d2(Point p1, Point p2) {
    return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> R;
    Point t, a, b, c;
    cin >> t.x >> t.y >> a.x >> a.y >> a.mass >> b.x >> b.y >> b.mass >> c.x >> c.y >> c.mass;
    vector<Point> p = {a,b,c};
    sort(p.begin(),p.end());
    if (d2(t,p.front()) < R*R) {
        cout << "What a beauty!\n";
    }
    else {
        cout << "Time to move my telescope!\n";
    }

    return 0;
}

