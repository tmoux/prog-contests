/*
ID: silxikys
PROG: 
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

const double n0 = 1;
const double space = 50;

double gamma(double e) {
	return (e / 0.016);
}



double newamtleft(double k, double& e0, double space, double st) {
	double start = st;
	for (int i = 1; i <= k; i++) {
		start *= exp(-500000*(space/(3*100000000))/gamma(e0+.025*(i-1)));

	}
	e0 += .025*k;
	return start;
}


int main() {
	t1 = gettime();
	ofstream fout(".out");
	ifstream fin("yinyang.in");

	double k, e0, space;
	fin >> k >> e0 >> space;


	double numlinear = 290;
	double numsmall = 448;
	double smallrev = 12;
	double nummed = 710;
	double medrev = 12;
	double bigcirc = 28290*2*3.1415;
	double bigrev = 120;
	space = 10;
	double totaltomed = numlinear+numsmall*smallrev+nummed*medrev;
	double numbig = bigcirc/space*bigrev;
	
	cout << totaltomed << '\n' << numbig << '\n';
	double currEnergy = 0.00075;
	double uptomedium = newamtleft(totaltomed,currEnergy,0.5,1.0);
	double totalleft = newamtleft(numbig,currEnergy,space,uptomedium);
	cout << "up to medium: " << uptomedium << '\n';
	cout << "total left: " << totalleft << '\n';
	endProgram(t1);
	return 0;
}