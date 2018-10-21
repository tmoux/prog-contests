/*
ID: silxikys
PROG: billboard
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

ofstream fout("billboard.out");
ifstream fin("billboard.in");

struct Rectangle {
	int minx;
	int maxx;
	int miny;
	int maxy;
	int area() {
		return (maxy-miny)*(maxx-minx);
	}
	Rectangle intersect(Rectangle a) {
		int minxx = max(minx,a.minx);
		int minyy = max(miny,a.miny);
		int maxxx = min(maxx,a.maxx);
		int maxyy = min(maxy,a.maxy);
		Rectangle ret = {minxx,maxxx,minyy,maxyy};
		if (ret.minx >= ret.maxx || ret.miny >= ret.maxy) {
			//degenerate case
			return {0,0,0,0};
		}
		return ret;
	}
};

int main() 
{
	Rectangle recs[3];
	for (int i = 0; i < 3; i++) {
		int x1, y1, x2, y2;
		fin >> x1 >> y1 >> x2 >> y2;
		recs[i] = {x1,x2,y1,y2};
	}
	/*
	for (Rectangle r: recs) {
		cout << r.minx << ' ' << r.miny << ' ' << r.maxx << ' ' << r.maxy << '\n';
	}
	*/

	Rectangle inter1 = recs[0].intersect(recs[2]);
	Rectangle inter2 = recs[1].intersect(recs[2]);

	cout << inter1.minx << ' ' << inter1.miny << ' ' << inter1.maxx << ' ' << inter1.maxy << '\n';

	int ans = recs[0].area() + recs[1].area() - inter1.area() - inter2.area();
	cout << ans << '\n';
	fout << ans << '\n';



	return 0;
}