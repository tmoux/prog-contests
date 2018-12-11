/*
ID: silxikys
PROG: packrec
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

struct Rectangle
{
	int h;
	int w;

	Rectangle() {

	}
	Rectangle(int a, int b) {
		h = a;
		w = b;
	}

	bool operator<(Rectangle rhs) {
		return h < rhs.h;
	}

	bool operator==(const Rectangle& rhs) {
		return (h == rhs.h && w == rhs.w);
	}
};

int minarea = 9999999;
vector<Rectangle> sols;

int max(int a, int b, int c) {
	return max(a,max(b,c));
}

int max(int a, int b, int c, int d) {
	return max(max(a,b,c),d);
}

int area(Rectangle r) {
	return r.h * r.w;
}

Rectangle minimize(Rectangle r) {
	if (r.h > r.w) {
		return {r.w,r.h};
	}
	return r;
}

Rectangle recs[4][2];
Rectangle permutes[24][4][2];
int nPermutes = 0;

void swap(int* arr, int a, int b) {
	int* x = arr+a;
	int* y = arr+b;
	int temp = *x;
	*x = *y;
	*y = temp;
}

void findPermutes(int a[], int l, int r) {
	if (l == r) {
		Rectangle add[4][2] = {recs[a[0]],recs[a[1]],recs[a[2]],recs[a[3]]};
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 2; j++) {
				permutes[nPermutes][i][j] = add[i][j];
			}
		}
		nPermutes++;
	}
	else {
		for (int i = l; i < r; i++) {
			swap(a,l,i);
			findPermutes(a,l+1,r);
			swap(a,l,i);
		}
	}
}

ostream& operator<<(ostream& os, const Rectangle& r) {
	os << r.h << ' ' << r.w;
	return os;
}
int main() {
	t1 = gettime();
	ofstream fout("packrec.out");
	ifstream fin("packrec.in");

	for (int i = 0; i < 4; i++) {
		int length, width; fin >> length >> width;
		recs[i][0] = {length, width};
		recs[i][1] = {width, length};
	}

	int test[4] = {0,1,2,3};
	findPermutes(test,0,4);


	for (int a = 0; a < 24; a++) {
		for (Rectangle i: permutes[a][0]) {
			for (Rectangle j: permutes[a][1]) {
				for (Rectangle k: permutes[a][2]) {
					for (Rectangle l: permutes[a][3]) {
						//cout << i << '\n' << j << '\n' << k << '\n' << l << "\n\n";
						Rectangle finds[7];
						finds[0] = {i.w+j.w+k.w+l.w,max(i.h,j.h,k.h,l.h)};
						finds[1] = {max(i.h,j.h,k.h)+l.h,max(l.w,i.w+j.w+k.w)};
						finds[2] = {max(k.h,i.h+l.h,j.h+l.h),max(i.w+j.w+k.w,l.w+k.w)};
						finds[3] = {max(i.h,j.h+k.h,l.h),i.w+l.w+max(j.w,k.w)};
						finds[4] = {max(i.h+j.h,k.h,l.h),k.w+l.w+max(i.w,j.w)};

						if (j.h < l.h) {
							finds[5] = {max(i.h,k.h)+max(j.h,l.h),max(i.w,j.w)+max(k.w,l.w)};
						}
						else {
							finds[5] = {max(i.h,k.h)+max(j.h,l.h),max(i.w+k.w,j.w+l.w)};
						}

						for (int qwer = 0; qwer < 6; qwer++) {
							Rectangle r = finds[qwer];
							//cout << r << '\n';
							if (area(r) < minarea) {
								minarea = area(r);
								sols = {minimize(r)};

								//cout << i << '\n' << j << '\n' << k << '\n' << l << "\n\n";
								//cout << qwer << ' ' << area(r) << "\n\n\n"; 
							}
							else if (area(r) == minarea) {
								if (find(sols.begin(),sols.end(),minimize(r)) == sols.end()) {
									sols.push_back(minimize(r));
								}
							}
						}
						//cout << minarea << '\n';
					}

				}
			}
		}
	}

	//output
	cout << area(sols[0]) << '\n';
	fout << area(sols[0]) << '\n';
	sort(sols.begin(),sols.end());
	for (Rectangle r: sols) {
		cout << r << '\n';
		fout << r << '\n';
	}


	
	
	endProgram(t1);
	return 0;
}