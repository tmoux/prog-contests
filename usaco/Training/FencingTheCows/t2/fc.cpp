/*
ID: silxikys
LANG: C++11
TASK: fc
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) begin(x),end(x)
const double EPS = 1e-10;
struct Point
{
	double x, y;
	bool operator<(const Point& A) const 
	{
		return x < A.x || (abs(x-A.x) <= EPS && y < A.y);
	}
	Point operator-(const Point& A) {
		return {x-A.x,y-A.y};
	}
};

double Cross(Point A, Point B) {
	return A.x * B.y - A.y * B.x;
}

double sqr(double x) { return x*x; }

double dist(Point A, Point B) {
	return sqrt(sqr(A.x-B.x)+sqr(A.y-B.y));
}

int N;

void refreshHull(const vector<Point>& toadd, vector<Point>& points, vector<Point>& hull) {
	points.insert(points.end(),all(toadd));
	sort(all(points));
	int n = points.size();
	/*
	for (Point p: points) {
		cout << p.x << ' ' << p.y << '\n';
	}
	*/
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
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cout << fixed << setprecision(2);
    freopen("fc.in","r",stdin); freopen("fc.out","w",stdout);
    cin >> N;
    vector<Point> points, hull;
    for (int i = 0; i < N; i++) {
    	double x, y; cin >> x >> y;
    	points.push_back({x,y});
    }
    refreshHull({},points,hull);
    double res = 0;
    for (int i = 0; i < hull.size() - 1; i++) {
    	res += dist(hull[i],hull[i+1]);
    }
    cout << res << '\n';
    for (Point p: hull) {
    	//cout << p.x << ' ' << p.y << '\n';
    }

    return 0;
}