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
	
	if (dist(F,C) >= R) {
		cout << C.x << ' ' << C.y << ' ' << R << '\n';
		return 0;
	}
	double dy = y1-y2;
	double dx = x1-x2;
	//cout << dy << ' ' << dx << '\n';
	//cout << R*cos(atan2(dy,dx)) << '\n';
	Point C2 = {(C.x + F.x + R*cos(atan2(dy,dx)))/2,(C.y+F.y+R*sin(atan2(dy,dx)))/2};
	double r = dist(C2,F);
	cout << setprecision(10) << C2.x << ' ' << C2.y << ' ' << r << '\n';
		
	return 0;
}

