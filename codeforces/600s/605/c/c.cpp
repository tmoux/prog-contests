#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define all(x) begin(x),end(x)

const int maxn = 1e5+5;
int N;

template <typename T>
struct Point
{
    T x, y;
    bool operator<(const Point& A) const
    {
        return x < A.x || (x == A.x && y < A.y);
    }
    Point operator-(const Point& A) {
        return {x-A.x,y-A.y};
    }
    Point operator*(T a) {
        return {a*x,a*y};
    }
};

typedef Point<ll> iPoint;
typedef Point<ld> dPoint;

template <typename T>
T Cross(Point<T> A, Point<T> B) {
    return A.x * B.y - A.y * B.x;
}

template <typename T>
T Dot(Point<T> A, Point<T> B) {
    return A.x*B.x + A.y*B.y;
}

vector<iPoint> points;
vector<iPoint> hull;

void buildHull() {
    sort(all(points));
    int n = points.size();
    hull.resize(points.size()+2);
    int m = 0;
    for (int i = 0; i < n; i++) {
        while (m > 1 && Cross(hull[m-1]-hull[m-2],points[i]-hull[m-2]) <= 0) {
            m--;
        }
        hull[m++] = points[i];
    }
    int k = m;
    for (int i = n - 2; i >= 0; i--) {
        while (m > k && Cross(hull[m-1]-hull[m-2],points[i]-hull[m-2]) <= 0) {
            m--;
        }
        hull[m++] = points[i];
    }
    hull.resize(m);
}

dPoint P;

dPoint proj(dPoint a, dPoint b) {
    dPoint v = b - a;
    ld s = Dot(P-a,v)/Dot(v,v);
    return {s*v.x+a.x,s*v.y+a.y};
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    cin >> P.x >> P.y;
    for (int i = 0; i < N; i++) {
        ll x, y; cin >> x >> y;
        points.push_back({x,y});
    }
    //points.push_back({0,0});
    buildHull();
    /*
    for (auto p: hull) {
        cout << p.x << ' ' << p.y << '\n';
    }
    */
    ld lo = 0, hi = 1e7+6;
    for (int q = 0; q < 200; q++) {
        ld mid = (lo+hi)/2;
        bool poss = false;
        for (int i = 0; i < hull.size(); i++) {
            ld x = hull[i].x*mid;
            ld y = hull[i].y*mid;
            if (x >= P.x && y >= P.y) {
                poss = true;
                break;
            }
        }
        for (int i = 0; i < (int)hull.size()-1; i++) {
            dPoint a = {hull[i].x*mid,hull[i].y*mid};
            dPoint b = {hull[i+1].x*mid,hull[i+1].y*mid};
            //printf("(%d, %d), (%d, %d)\n",hull[i].x,hull[i].y,hull[i+1].x,hull[i+1].y);
            //cout << a.x << ' ' << a.y << ' ' << b.x << ' ' << b.y << endl;
            dPoint d = proj(a,b);
            //cout << d.x << ' ' << d.y << '\n';
            if (min(a.x,b.x) <= d.x &&
                d.x <= max(a.x,b.x) &&
                min(a.y,b.y) <= d.y &&
                d.y <= max(a.y,b.y) &&
                d.x >= P.x && d.y >= P.y) {
                poss = true;
                break;
            }
        }
        if (poss) {
            hi = mid;
        }
        else {
            lo = mid;
        }
    }
    cout << fixed << setprecision(10) << hi << '\n';
}

