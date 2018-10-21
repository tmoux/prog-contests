/*
ID: silxikys
PROG: fc
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
#include <iomanip>
using namespace std;
using namespace std::chrono;

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1;

const int maxn = 10000;
double xi[maxn], yi[maxn], angle[maxn];
double midx = 0, midy = 0;
pair<double,double> perm[maxn], hull[maxn];

int N;

double zcrossprod(pair<double,double> u, pair<double,double> v) {
	return u.first*v.second - u.second*v.first;
}

double aangle(double x,double y) {
	double a = double(atan2(y - midy, x - midx));
	if (a < 0) {
		return a + 6.28319;
	}
	return a;
}

double ddistance(pair<double,double> u, pair<double,double> v) {
	return (pow(pow(u.first-v.first,2.0)+pow(u.second-v.second,2.0),0.5));
}

int main() {
	t1 = gettime();
	ofstream fout("fc.out");
	ifstream fin("fc.in");

	//input
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> xi[i];
		fin >> yi[i];
	}

	//finds mid-point
	for (int i = 0; i < N; i++) {
		midx += xi[i]/N;
		midy += yi[i]/N;
		perm[i] = make_pair(xi[i],yi[i]);
	}

	sort(perm,perm+N,[](const pair<double,double> &lhs, const pair<double,double> &rhs) {
		return aangle(lhs.first,lhs.second) < aangle(rhs.first,rhs.second);
	});

	//create convex hull
	hull[0] = perm[0];
	hull[1] = perm[1];
	int hullpos = 2;
	for (int i = 2; i < N - 1; i++) {
		pair<double,double> p = perm[i];
		while (hullpos > 1 && zcrossprod(make_pair(hull[hullpos-2].first-hull[hullpos-1].first, hull[hullpos-2].second-hull[hullpos-1].second),make_pair(hull[hullpos-1].first-p.first,hull[hullpos-1].second-p.second)) < 0) {

			hullpos--;
		}
		hull[hullpos] = p;
		hullpos++;			
	}
	/*
	for (int i = 0; i < hullpos; i++) {
		pair<double,double> p = hull[i];
		cout << p.first << ' ' << p.second << '\n';
	} cout << '\n';
	*/
	//////////////////////////
	//add LAST point
	pair<double,double> p = perm[N-1];
	while (hullpos > 1 && zcrossprod(make_pair(hull[hullpos-2].first-hull[hullpos-1].first, hull[hullpos-2].second-hull[hullpos-1].second),make_pair(hull[hullpos-1].first-p.first,hull[hullpos-1].second-p.second)) <= 0) {
		hullpos--;
	}

	int hullstart = 0;
	bool flag;
	do {
		flag = false;
		if (hullpos - hullstart >= 2 && zcrossprod(make_pair(p.first-hull[hullpos-1].first, p.second-hull[hullpos-1].second),make_pair(hull[hullstart].first-p.first,hull[hullstart].second-p.second)) <= 0) {
			p = hull[hullpos-1];
			hullpos--;
			flag = true;
		}
		if (hullpos - hullstart >= 2 && zcrossprod(make_pair(hull[hullstart].first-p.first, hull[hullstart].second-p.second),make_pair(hull[hullstart+1].first-hull[hullstart].first,hull[hullstart+1].second-hull[hullstart].second)) <= 0) {
			hullstart++;
			flag = true;
		}
	} while (flag);

	hull[hullpos] = p;
	hullpos++;  

	//calculate perimeter
	double perimeter = ddistance(hull[0],hull[hullpos-1]);
	for (int i = 0; i < hullpos - 1; i++) {
		pair<double,double> a = hull[i];
		pair<double,double> q = hull[i+1];
		perimeter += ddistance(a,q);

		cout << a.first << " " << a.second << endl;
	} cout << hull[hullpos-1].first << " " << hull[hullpos-1].second << endl;

	cout << fixed << setprecision(2) << perimeter << '\n';
	fout << fixed << setprecision(2) << perimeter << '\n';

	
	endProgram(t1);
	return 0;
}