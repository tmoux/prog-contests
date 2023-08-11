#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;

struct Point
{
	double x;
	double y;
};

double dist(Point a, Point b) {
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

double yx(double x, double m, double b) {
	return m*x+b;
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	
	Point C, F;
	double R, x1, y1, x2, y2;
	cin >> R >> x1 >> y1 >> x2 >> y2;
	C = {x1,y1}; F = {x2,y2};
	if (F.x-C.x != 0) {
	double m = (F.y-C.y)/(F.x-C.x);
	double b = F.y - m*F.x;
	//cout << b << '\n';
	Point P1, P2;
	double dx = sqrt(R*R/(m*m+1));
	Point C2;
	double r;
	if (dist(F,C) >= R) {
		C2 = C;
		r = R;
	}
	
	else {
		P1 = {C.x+dx,yx(C.x+dx,m,b)};
		if (dist(P1,F) > dist(P1,C)) {
			P2 = F;
		}
		else {
			P2 = P1;
			P1 = F;
		}
		C2 = {(P1.x+P2.x)/2,(P1.y+P2.y)/2};
		r = min(dist(C2,P1),dist(C2,P2));
	}
	//cout << P1.x << ' ' << P1.y << '\n';
	//cout << P2.x << ' ' << P2.y << ' ' << '\n';
	cout << setprecision(9) << C2.x << ' ' << C2.y << ' ' << r << '\n';
	}
	else {
		Point P1, P2, C2;
		double r;
		if (dist(F,C) >= R) {
			P1 = {C.x,C.y+R};
			P2 = {C.x,C.y-R};
			C2 = {C.x,C.y};
			r = R;
		}
		else {
			P1 = {C.x,C.y+R};
			if (dist(P1,F) > dist(P1,C)) {
				P2 = F;
			}
			else {
				P2 = P1;
				P1 = F;
			}
			C2 = {(P1.x+P2.x)/2,(P1.y+P2.y)/2};
			r = min(dist(C2,P1),dist(C2,P2));
		}
		cout << setprecision(9) << C2.x << ' ' << C2.y << ' ' << r << '\n';
	}
	
	
	return 0;
}

