#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) begin(x),end(x)

const int maxn = 1e5+5;
int N, Q;

struct Point
{
	double x, y;
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

T Cross(Point<T> A, Point<T> B) {
	return A.x * B.y - A.y * B.x;
}

vector<Point> points;

template <typename T>
T det(T A, T B, T C, T D) {
	return A*D-B*C;
}

const double EPS = 1e-8;
struct Line
{
    double A, B, C; //Ax + By = C
    Point v1, v2;
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
    Line(dPoint a, dPoint b) {
        v1 = a;
        v2 = b;
        A = b.y-a.y;
        B = a.x-b.x;
        C = a.x*b.y-b.x*a.y;
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
		double x, y; cin >> x >> y;
		points.push_back({x,y});
	} 

	while (Q--) {
		int t; cin >> t;
		if (t == 1) {
			double x, y; cin >> x >> y;
			points.push_back({x,y});
		}
		else {
			double A, B, C; cin >> A >> B >> C;
			Line l1 = Line(A,B,C);
			bool poss = true;
			int c1 = l1.p_cross(points.front());
			if (c1 == 0) poss = false;
			else for (dPoint p: points) {
				int c2 = l1.p_cross(p);
				if (c2 != c1) {
					poss = false;
					break;
				}
			}
			cout << (poss?"YES":"NO") << '\n';
		}
	}

    return 0;
}