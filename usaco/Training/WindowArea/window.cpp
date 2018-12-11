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

double pctvisible(int orig, int intersect) {
	return (double(orig - intersect) / orig) * 100;
}

void makeCombinations(int reqlength, int start, int maxindex, vector<vector<int>> &stores,vector<int> combo = {}) {

	if (combo.size() == reqlength) {
		//do stuff with combo vector
		stores.push_back(combo);
	}
	else {
		for (int i = start; i < maxindex; i++) {
			combo.push_back(i);
			makeCombinations(reqlength,i+1,maxindex,stores,combo);
			combo.pop_back();
		}
	}
}

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
};

map<char,Rectangle> convert;
deque<char> deq;

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
			//do stuff
			/*
			printf("operation: %c \nidentifier: %c \ncoordinates: (%d,%d) and (%d,%d) \n\n",operation,identifier,minx,miny,maxx,maxy);
			*/
			Rectangle add = Rectangle(minx,miny,maxx,maxy);
			deq.push_back(identifier);
			convert[identifier] = add;
		}
		else {
			fscanf(pfile,")\n");
			//do stuff
			/*
			printf("operation: %c \nidentifer: %c \n\n",operation,identifier);
			*/
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
					//do the summing + and - thing and print the answer
					//cout << index << endl;
					int flipper = 1;
					double amtCovered = 0;
					for (int length = 1; length < deq.size() - index; length++) {
						vector<vector<int>> intersects;
						makeCombinations(length,index+1,deq.size(),intersects);
						for (vector<int> v: intersects) {
							Rectangle r = convert[deq[index]];
							for (int i : v) {
								r = r.intersect(convert[deq[i]]);
								
							}
							amtCovered += r.area * flipper;
						}
						flipper *= -1; 
					}
					cout << pctvisible(convert[deq[index]].area,amtCovered) << '\n';
					fprintf(ofile,"%.3f\n",pctvisible(convert[deq[index]].area,amtCovered));
					break;

			}
		}
	}


	/*
	Rectangle a = Rectangle(0,0,3,3);
	Rectangle b = Rectangle(3,3,5,5);
	Rectangle c = Rectangle(-1,-2,3,1);
	Rectangle i = a.intersect(b.intersect(c));

	cout << a.area << endl;
	printf("(%d,%d), (%d,%d), area = %d \npercentage of a seen is %.3f",i.minx,i.miny,i.maxx,i.maxy,i.area,pctvisible(a.area,i.area));
	*/

	
	endProgram(t1);
	return 0;
}