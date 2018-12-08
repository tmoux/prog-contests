#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) begin(x),end(x)
//just to establish all the geo (line class, line intersection, polygon-line intersection works

const int maxn = 1e5+5;
int N, Q;

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

typedef Point<int> iPoint;
typedef Point<double> dPoint;

template <typename T>
T Cross(Point<T> A, Point<T> B) {
	return A.x * B.y - A.y * B.x;
}

template <typename T, typename U>
double dist(Point<T> a, Point<U> b) {
    return sqrt((double)(a.x-b.x)*(a.x-b.x)+(double)(a.y-b.y)*(a.y-b.y));
}

vector<iPoint> points;
vector<iPoint> hull;

void refreshHull(const vector<iPoint>& toadd) {
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

template <typename T>
T det(T A, T B, T C, T D) {
	return A*D-B*C;
}

dPoint convertDouble(iPoint p) {
    return {(double)p.x,(double)p.y};
}

const double EPS = 1e-8;
struct Line
{
    ll A, B, C; //Ax + By = C
    dPoint v1, v2;
    Line(ll Ai, ll Bi, ll Ci) {
        A = Ai;
        B = Bi;
        C = Ci;
    }
    Line(ll x1, ll y1, ll x2, ll y2) {
        v1 = {(double)x1,(double)y1};
        v2 = {(double)x2,(double)y2};
        A = y2-y1;
        B = x1-x2;
        C = x1*y2-x2*y1;
    }

    bool isParallel(Line l2) {
        return det(A,B,l2.A,l2.B) == 0;
    }

    dPoint getPoint() {
        if (A == 0) {
            return {0,(double)(C)/B};    
        }
        if (B == 0) {
            return {(double)(C)/A,0};
        }
        return {0,(double)(C)/B};
    }

    dPoint intersection(Line l2) {
        assert(!isParallel(l2));
        ll dd = det(A,B,l2.A,l2.B);
        return {(double)(det(C,B,l2.C,l2.B))/dd,(double)(det(A,C,l2.A,l2.C))/dd};
    }

    bool isBetween(dPoint p) { //assumes p is on the line
        return min(v1.x,v2.x) <= p.x && p.x <= max(v1.x,v2.x) && min(v1.y,v2.y) <= p.y && p.y <= max(v1.y,v2.y);
    }

    int p_cross(dPoint p) { //-1 is left of line, 0 is on the line, 1 is right of line
        double cross = Cross(v2-v1,p-v1);    
        //cout << cross << '\n';
        if (abs(cross) <= EPS) return 0;
        return cross < 0 ? -1 : 1;
    }

    bool intersectSegment(iPoint a, iPoint b) {
        Line l2(a.x,a.y,b.x,b.y);
        if (isParallel(l2)) return false;
        dPoint inter = intersection(l2);
        //cout << inter.x << ' ' << inter.y << '\n';
        return l2.isBetween(inter);
    }
};

bool intersectHull(Line l1, int v0, int vn, const vector<iPoint>& hull) { //returns TRUE if intersects polygon, otherwise FALSE
	if (v0 == vn) return false;
    if ((vn-v0) <= 4) {
        bool poss = false;
        for (int i = v0; i < vn; i++) {
            poss |= l1.intersectSegment(hull[i],hull[i+1]);
        }
        return poss;
    }
    int vm = (v0+vn)/2;
    Line vsplit(hull[v0].x,hull[v0].y,hull[vm].x,hull[vm].y);
    if (l1.isParallel(vsplit)) {
        int c1 = vsplit.p_cross(l1.getPoint());
        int c2 = vsplit.p_cross(convertDouble(hull[v0+1]));    
        if (c1 == c2) {
            return intersectHull(l1,v0,vm,hull);
        }
        else {
            return intersectHull(l1,vm,vn,hull);    
        }
    }
    else {
        dPoint p = l1.intersection(vsplit);
        if (vsplit.isBetween(p)) return true;
        //case 2.2: intersection closer to v0
        if (dist(p,hull[v0]) < dist(p,hull[vm])) {
            Line border(hull[v0].x,hull[v0].y,hull[v0+1].x,hull[v0+1].y);
            if (l1.isParallel(border)) return false;
            dPoint inter = l1.intersection(border);
            if (vsplit.p_cross(inter) == vsplit.p_cross(convertDouble(hull[v0+1]))) {
                return intersectHull(l1,v0,vm,hull);
            }
            else {
                return intersectHull(l1,vm,vn,hull);
            }
        }
        else {
            Line border(hull[vm].x,hull[vm].y,hull[vm+1].x,hull[vm+1].y);
            if (l1.isParallel(border)) return false;
            dPoint inter = l1.intersection(border);
            if (vsplit.p_cross(inter) == vsplit.p_cross(convertDouble(hull[vm+1]))) {
                return intersectHull(l1,vm,vn,hull);
            }
            else {
                return intersectHull(l1,v0,vm,hull);
            }
        }
    }
}

int main()
{
	scanf("%d %d\n",&N,&Q);
	for (int i = 0; i < N; i++) {
		int x, y; scanf("%d %d\n",&x,&y);
		points.push_back({x,y});
	}
	refreshHull({});
    /*
    for (iPoint p: hull) {
        cout << p.x << ' ' << p.y << '\n';
    }
    */
    Line l1(2,10,50);
    cout << intersectHull(l1,0,hull.size()-1,hull);

    return 0;
}
