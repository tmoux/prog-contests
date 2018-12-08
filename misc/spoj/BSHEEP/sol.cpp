#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) begin(x),end(x)

const int maxn = 1e5+5;
int N, Q;

struct Point
{
	int x, y;
	bool operator<(const Point& A) const 
	{
		return y < A.y || (y == A.y && x < A.x);
	}
	Point operator-(const Point& A) {
		return {x-A.x,y-A.y};
	}
};

int Cross(Point A, Point B) {
	return A.x * B.y - A.y * B.x;
}

double sqr(double x) {return x*x;}

double dist(Point A, Point B) {
	return sqrt(sqr(A.x-B.x)+sqr(A.y-B.y));
}

vector<Point> points;
vector<Point> hull;

void refreshHull(const vector<Point>& toadd) {
	points.insert(points.end(),all(toadd));
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

map<pair<int,int>,int> mp;

void output(vector<Point>& pts) {
	Point xp = {100000,100000};
	int idx;
	for (int i = 0; i < pts.size() - 1; i++) {
		if (pts[i] < xp) {
			xp = pts[i];
			idx = i;
		}
	}
	for (int i = idx; i < idx+pts.size()-1; i++) {
		int j = i % (pts.size() - 1);
		cout << mp[{pts[j].x,pts[j].y}] << ' ';
	}
}

int main()
{
	int t; cin >> t;
	cout << fixed << setprecision(2);
	while (t--) {
		int n; cin >> n;
		points.clear();
		mp.clear();
		for (int i = 0; i < n; i++) {
			int x, y; cin >> x >> y;
			if (!mp.count({x,y})) {
				points.push_back({x,y});
				mp[{x,y}] = i + 1;
			}
		}
		refreshHull({});
		double perim = 0;
		for (int i = 0; i < hull.size() - 1; i++) {
			perim += dist(hull[i],hull[i+1]);
		}
		cout << perim << '\n';
		//cout << "Size: " << hull.size() << '\n';
		if (hull.size() == 1) {
			cout << mp[{hull[0].x,hull[0].y}] << '\n';
			cout << '\n';
			continue;
		}
		else if (hull.size() == 3) {
			//cout << "ASDF\n";
			sort(hull.begin(),hull.begin()+2);
			for (int i = 0; i <= 1; i++) {
				cout << mp[{hull[i].x,hull[i].y}] << ' ';
			}
			cout << "\n\n";
			continue;
		}
		output(hull);
		cout << "\n\n";
	}
    return 0;
}