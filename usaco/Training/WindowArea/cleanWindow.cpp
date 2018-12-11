/*
ID: silxikys
PROG: window
LANG: C++11
*/

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <climits>
#include <array>
#include <chrono>
#include <math.h>
#include <deque>
using namespace std;
using namespace std::chrono;

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1;

struct Rectangle{
	int minx, miny, maxx, maxy, area;
	Rectangle() {
		minx = 0;
		miny = 0;
		maxx = 0;
		maxy = 0;
		area = 0;
	}
	Rectangle(int minxx,int minyy,int maxxx,int maxyy) {
		minx = minxx;
		miny = minyy;
		maxx = maxxx;
		maxy = maxyy;
		area = (abs(maxy-miny) * abs(maxx-minx));
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
				ret.push_back(Rectangle(q.minx, q.miny, r.minx, q.maxy));
			}
			if (q.maxx > r.maxx) {
				ret.push_back(Rectangle(r.maxx, q.miny, q.maxx, q.maxy));
			}
			if (q.maxy > r.maxy) {
				ret.push_back(Rectangle(max(r.minx,q.minx), r.maxy, min(r.maxx,q.maxx), q.maxy));
			}
			if (q.miny < r.miny) {
				ret.push_back(Rectangle(max(r.minx,q.minx), q.miny, min(r.maxx,q.maxx), r.miny));
			}
		}
		else {
			ret.push_back(q);
		}
	}
	return ret;
}

//globals
map<char,Rectangle> convert;
deque<Rectangle> deq;

int main() {
	t1 = gettime();
	ofstream fout("window.out");
	ifstream fin("window.in");
	FILE * pfile;
	pfile = fopen("window.in","r");
	FILE * ofile;
	ofile = fopen("window.out","w");

	char operation, identifier;
	int x, y, X, Y, minx, miny, maxx, maxy;
	while (fscanf(pfile,"%c(%c,",&operation,&identifier) != EOF) 
	{
		if (operation == 'w') {
			fscanf(pfile,"%d,%d,%d,%d)\n",&x,&y,&X,&Y);
			minx = min(x,X);
			maxx = max(x,X);
			miny = min(y,Y);
			maxy = max(y,Y);

			Rectangle add = Rectangle(minx,miny,maxx,maxy);
			deq.push_back(identifier);
			convert[identifier] = add;
		}
		else {
			fscanf(pfile,")\n");
			switch (operation) {
				case 't':
					//bring window to top
					deq.erase(remove(deq.begin(),deq.end(),identifier));
					deq.push_back(identifier);
					break;
				case 'b':
					deq.erase(remove(deq.begin(),deq.end(),identifier));
					deq.push_front(identifier);
					break;
				case 'd':
					deq.erase(remove(deq.begin(),deq.end(),identifier));
					convert.erase(identifier);
					break;
				case 's':
					int index = 0;
					while (deq[index] != identifier) {
						index++;
					}
					//create Rect vector, for each window above it, intersect with all
					//rectangles and create more rectangles
					//At the end, sum all areas of the rectangles in the vector
					vector<Rectangle> recs = {convert[deq[index]]};
					for (int i = index + 1; i < deq.size(); i++) {
						recs = intersplit(recs, convert[deq[i]]);
					}
					//sum areas in recs
					int uncovered = 0;
					for (Rectangle r: recs) {
						uncovered += r.area;
					}
					double ans = double(uncovered) / convert[deq[index]].area * 100;
					fprintf(ofile,"%.3f\n",ans);
					break;

			}
		}
	}

	endProgram(t1);
	return 0;
}