/*
ID: silxikys
PROG: rect1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <climits>
#include <array>
#include <chrono> 
#include <math.h>
using namespace std;
using namespace std::chrono;

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1;

struct Rectangle{
	int minx, miny, maxx, maxy, area, color;
	Rectangle() {
		minx = 0;
		miny = 0;
		maxx = 0;
		maxy = 0;
		area = 0;
	}
	Rectangle(int minxx,int minyy,int maxxx,int maxyy, int colori=0) {
		minx = minxx;
		miny = minyy;
		maxx = maxxx;
		maxy = maxyy;
		area = (abs(maxy-miny) * abs(maxx-minx));
		color = colori;
	}
	Rectangle intersect(Rectangle a) {
		Rectangle ret = Rectangle();
		if (a.area == 0 || area == 0) {
			return ret;
		}
		int m1, m2, m3, m4;

		m1 = max(minx,a.minx);
		m2 = min(maxy,a.maxy);
		m3 = min(maxx,a.maxx);
		m4 = max(miny,a.miny);
		
		ret = Rectangle(m1,m4,m3,m2);
		if (ret.minx >= ret.maxx || ret.miny >= ret.maxy) {
			//degenerate case
			ret.area = 0;
		}
		return ret;
	}

	void print() {
		printf("(%d,%d), (%d,%d)\n",minx,miny,maxx,maxy);
	}
};

vector<Rectangle> intersplit(const vector<Rectangle>& recs, Rectangle r) {
	vector<Rectangle> ret;
	for (Rectangle q : recs) {
		if (r.intersect(q).area != 0) {
			if (q.minx < r.minx) {
				ret.push_back(Rectangle(q.minx, q.miny, r.minx, q.maxy,q.color));
			}
			if (q.maxx > r.maxx) {
				ret.push_back(Rectangle(r.maxx, q.miny, q.maxx, q.maxy,q.color));
			}
			if (q.maxy > r.maxy) {
				ret.push_back(Rectangle(max(r.minx,q.minx), r.maxy, min(r.maxx,q.maxx), q.maxy,q.color));
			}
			if (q.miny < r.miny) {
				ret.push_back(Rectangle(max(r.minx,q.minx), q.miny, min(r.maxx,q.maxx), r.miny,q.color));
			}
		}
		else {
			ret.push_back(q);
		}
	}
	ret.push_back(Rectangle(r.minx,r.miny,r.maxx,r.maxy,r.color));
	return ret;
}

map<int,Rectangle> convert;
int A, B, N;
int colors[2501];
vector<Rectangle> vec;

int main() {
	t1 = gettime();
	ofstream fout("rect1.out");
	ifstream fin("rect1.in");

	fin >> A >> B >> N;
	vec.push_back(Rectangle(0,0,A,B,1));
	for (int i = 0; i < N; i++) {
		int llx, lly, urx, ury, color;
		fin >> llx >> lly >> urx >> ury >> color;
		vec.push_back(Rectangle(llx,lly, urx, ury, color));
	}
	vector<Rectangle> recs = {vec[0]};
	for (Rectangle r: vec) {
		recs = intersplit(recs, r);
	}
	for (Rectangle r: recs) {
		colors[r.color] += r.area;
	}
	for (int i = 1; i <= 2500; i++) {
		if (colors[i]) {
			cout << i << ' ' << colors[i] << '\n';
			fout << i << ' ' << colors[i] << '\n';
		}
	}

	
	endProgram(t1);
	return 0;
}
