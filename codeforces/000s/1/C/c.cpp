#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = double;

struct Point
{
    ld x, y;
    Point() { x = 0, y = 0; }
    Point(ld _x, ld _y) {
        x = _x;
        y = _y;
    }

    Point operator-(Point a) {
        return Point(x-a.x,y-a.y);
    }

    Point rotate(ld angle) {
        ld s = sin(angle);
        ld c = cos(angle);
        return Point(x*c-y*s,x*s+y*c);
    }

    ld norm() {
        return sqrt(x*x+y*y);
    }
};

ld dot(Point a, Point b) {
    return a.x*b.x + a.y*b.y;
}

const ld PI = 4*atan(1);

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << fixed << setprecision(10);
    Point a, b, c;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    b = b-a;
    c = c-a;
    a = a-a;
    ld angle = atan2(b.y,b.x);
    b = b.rotate(-angle);
    c = c.rotate(-angle);
    /*
    cout << a.x << ' ' << a.y << endl;
    cout << b.x << ' ' << b.y << endl;
    cout << c.x << ' ' << c.y << endl;
    */
    Point mid = Point(c.x/2,c.y/2);
    ld slope = -mid.x/mid.y;
    ld intercept = mid.y - slope*mid.x;
    Point circ = Point(b.x/2,slope*b.x/2+intercept);
    Point A = a-circ;
    Point B = b-circ;
    Point C = c-circ;
    ld a1 = acos(dot(A,B)/(A.norm()*B.norm()));
    ld a2 = acos(dot(B,C)/(B.norm()*C.norm()));
    ld a3 = acos(dot(A,C)/(A.norm()*C.norm()));
    //cout << a1 << ' ' << a2 << ' ' << a3 << endl;
    for (int n = 3; n <= 100; n++) {
        ld d = (2*PI)/n;    
        double integer;
        //cout << n << ": " << d << endl;
        ld d1 = modf(a1/d,&integer);
        d1 = min(d1,1-d1);
        ld d2 = modf(a2/d,&integer);
        d2 = min(d2,1-d2);
        ld d3 = modf(a3/d,&integer);
        d3 = min(d3,1-d3);
        //cout << n << ": " << d1 << ' ' << d2 << ' ' << d3 << endl;
        /*
        ld area = n*A.norm()*A.norm()*sin(d)/2;
        cout << area << endl;
        */

        if (max(d1,max(d2,d3)) <= 1e-5) {
            ld area = n*A.norm()*A.norm()*sin(d)/2;
            cout << area << endl;
            return 0;
        }
    }
}
