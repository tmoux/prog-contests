#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) begin(x),end(x)

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

int W, H, R;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> W >> H >> R;
    cout << "2 2 0\n";
}

