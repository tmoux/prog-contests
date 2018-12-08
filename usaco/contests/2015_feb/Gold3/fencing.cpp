#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) begin(x),end(x)

const int maxn = 1e5+5;
int N, Q;

template <typename T>
struct Point
{
	T x, y;
	Point() {}
	Point(T _x, T _y) {
		x = _x;
		y = _y;
	}
	bool operator<(const Point& A) const 
	{
		return x < A.x || (x == A.x && y < A.y);
	}
	Point operator-(const Point& A) {
		return {x-A.x,y-A.y};
	}
};

typedef Point<ll> iPoint;
typedef Point<double> dPoint;

template <typename T>
T Cross(Point<T> A, Point<T> B) {
	return A.x * B.y - A.y * B.x;
}

double Cross(dPoint A, dPoint B) {
	return A.x * B.y - A.y * B.x;
}

vector<iPoint> points;
vector<iPoint> hull;

void refreshHull(vector<iPoint>& toadd) {
	points.insert(points.end(),all(toadd));
	toadd.clear();
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

const double EPS = 1e-5;
struct Line
{
    ll A, B, C; //Ax + By = C
    dPoint v1, v2;
    Line(ll Ai, ll Bi, ll Ci) {
        A = Ai;
        B = Bi;
        C = Ci;
        //fill in v1, v2
        if (A == 0) {
        	v1 = {0,(double)(C)/B};
        	v2 = {1,(double)(C)/B};
        }
        else if (B == 0) {
        	v1 = {(double)C/A,0};
        	v2 = {(double)C/A,1};
        }
        else if (C == 0) {
        	v1 = {1,(double)(-B)/A};
        	v2 = {(double)(-A)/B,1};        	
        }
        else {
        	v1 = {0,(double)(C)/B};
        	v2 = {(double)(C)/A,0};
        }
    }
    Line(ll x1, ll y1, ll x2, ll y2) {
        v1 = {(double)x1,(double)y1};
        v2 = {(double)x2,(double)y2};
        A = y2-y1;
        B = x1-x2;
        C = x1*y2-x2*y1;
    }

    int p_cross(dPoint p) { //-1 is left of line, 0 is on the line, 1 is right of line
        double cross = Cross(v2-v1,p-v1);    
        //cout << cross << '\n';
        if (abs(cross) <= EPS) return 0;
        return cross < 0 ? -1 : 1;
    }
};


int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("fencing.in","r",stdin); freopen("fencing.out","w",stdout);
	cin >> N >> Q;
	for (int i = 0; i < N; i++) {
		ll x, y; cin >> x >> y;
		points.push_back({x,y});
	} 

	vector<iPoint> toadd;
	refreshHull(toadd);
	
	/*
	for (int i = 0; i < hull.size() - 1; i++) {
		cout << hull[i].x << ' ' << hull[i].y << '\n';
	}
	*/
	while (Q--) {
		int t; cin >> t;
		if (t == 1) {
			ll x, y; cin >> x >> y;
			toadd.push_back({x,y});
			points.push_back({x,y});
			/*
			if (toadd.size() > sqrt(Q)) {
				refreshHull(toadd);
			}
			*/
		}
		else {
			//refreshHull(toadd);
			ll a, b, c; cin >> a >> b >> c;
			Line l1(a,b,c);

			bool poss = false;
			int c1 = l1.p_cross(convertDouble(points[0]));
			if (abs(c1) <= EPS) poss = true;
			//cout << "c1 = " << c1 << '\n';
			//printf("%d %d %d\n",l1.A,l1.B,l1.C);
			//printf("(%.2f, %.2f), (%.2f, %.2f)\n",l1.v1.x,l1.v1.y,l1.v2.x,l1.v2.y);
			for (iPoint p: points) {
				int c2 = l1.p_cross(convertDouble(p));
				//cout << "c2 = " << c2 << '\n';
				if (c2 != c1) {
					poss = true;
					break;
				}
			}
			cout << (poss?"NO":"YES") << '\n';
		}
	}

    return 0;
}