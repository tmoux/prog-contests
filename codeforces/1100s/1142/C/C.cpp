#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) begin(x),end(x)

const int maxn = 1e5+5;
int n;

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
};

typedef Point<ll> iPoint;

template <typename T>
T Cross(Point<T> A, Point<T> B) {
    return A.x * B.y - A.y * B.x;
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

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    ll maxX = -9999999;
    for (int i = 0; i < n; i++) {
        ll x, y; cin >> x >> y;
        maxX = max(maxX,x);
        points.push_back({x,y-x*x});
    }
    buildHull();
    reverse(all(hull));
    int ans = 0;
    for (int i = 0; i < hull.size(); i++) {
        if (hull[i].x == maxX) break;
        if (hull[i].x != hull[i+1].x) ans++;
    }
    cout << ans << '\n';
}

