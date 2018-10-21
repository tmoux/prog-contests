/*
ID: silxikys
PROG: split
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;

ofstream fout("split.out");
ifstream fin("split.in");

struct Point
{
	int x;
	int y;
};

const int maxn = 50002;
int N;
Point xsorted[maxn];
Point ysorted[maxn];

long long computeArea(const multiset<int>& xs, const multiset<int>& ys) {
	if (xs.empty() || ys.empty()) {
		return 0;
	}
	return (*xs.rbegin()-*xs.begin())*(*ys.rbegin()-*ys.begin());
}

long long twoRecArea(const multiset<int>& rec1x, const multiset<int>& rec1y, const multiset<int>& rec2x, const multiset<int>& rec2y) {
	return computeArea(rec1x,rec1y) + computeArea(rec2x,rec2y);
}

long long computeXY(Point arr[]) {
	multiset<int> rec1x, rec1y, rec2x, rec2y;
	for (int i = 0; i < N; i++) {
		rec2x.insert(arr[i].x);
		rec2y.insert(arr[i].y);
	}
	
	long long MinArea = twoRecArea(rec1x,rec1y,rec2x,rec2y);
	
	for (int i = 0; i < N; i++) {
		//erase one element from rec2x, rec2y
		multiset<int>::iterator itrX(rec2x.find(arr[i].x));
		multiset<int>::iterator itrY(rec2y.find(arr[i].y));
		if (itrX != rec2x.end()) rec2x.erase(itrX);
		if (itrY != rec2y.end()) rec2y.erase(itrY);
		//add the element to rec1x, rec1y
		rec1x.insert(arr[i].x);
		rec1y.insert(arr[i].y);

		MinArea = min(MinArea,twoRecArea(rec1x,rec1y,rec2x,rec2y));
	}
	
	return MinArea;
}

int main() 
{
	fin >> N;
	for (int i = 0; i < N; i++) {
		int x, y; fin >> x >> y;
		xsorted[i] = {x,y};
		ysorted[i] = xsorted[i];
	}
	sort(xsorted,xsorted+N,[](const Point& a, const Point& b) {
		if (a.x != b.x) {
			return a.x < b.x;
		}
		return a.y < b.y;
	});
	sort(ysorted,ysorted+N,[](const Point& a, const Point& b) {
		if (a.y != b.y) {
			return a.y < b.y;
		}
		return a.x < b.x;
	});

	//compute one rectangle area
	long long origArea = (xsorted[N-1].x-xsorted[0].x) * (ysorted[N-1].y-ysorted[0].y);

	//compute x-sorted min area of 2 rectangles
	long long xMinArea = computeXY(xsorted);
	//compute y-worted min area of 2 rectangles 
	long long yMinArea = computeXY(ysorted);

	long long ans = origArea - min(xMinArea,yMinArea);
	cout << ans << '\n';
	fout << ans << '\n';

	return 0;
}