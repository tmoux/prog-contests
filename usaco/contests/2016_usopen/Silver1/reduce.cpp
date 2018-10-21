/*
ID: silxikys
PROG: reduce
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

ofstream fout("reduce.out");
ifstream fin("reduce.in");

int N;
vector<pair<int,int>> cows;

int main() 
{
	fin >> N;
	vector<int> xs;
	vector<int> ys;
	for (int i = 0; i < N; i++) {
		int a, b; fin >> a >> b;
		cows.push_back(make_pair(a,b));
		if (find(xs.begin(),xs.end(),a) == xs.end()) {
			xs.push_back(a);
		}
		if (find(ys.begin(),ys.end(),b) == ys.end()) {
			ys.push_back(b);
		}
	}

	sort(xs.begin(),xs.end());
	sort(ys.begin(),ys.end());

	vector<int> minxs(xs.begin(),xs.begin()+4);
	vector<int> maxxs(xs.end()-4,xs.end());
	vector<int> minys(ys.begin(),ys.begin()+4);
	vector<int> maxys(ys.end()-4,ys.end());

	int ans = -1;
	for (int minx: minxs) {
		for (int maxx: maxxs) {
			for (int miny: minys) {
				for (int maxy: maxys) {
					int numExcluded = 0;
					for (pair<int,int> p: cows) {
						if (p.first < minx || p.first > maxx || p.second < miny || p.second > maxy) {
							numExcluded++;
						}
					}
					if (numExcluded <= 3) {
						//valid rectangle
						if (ans == -1) {
							ans = (maxy-miny)*(maxx-minx);
						}
						else {
							ans = min(ans,(maxy-miny)*(maxx-minx));
						}
					}
				}
			}
		}
	}

	cout << ans << '\n';
	fout << ans << '\n';
	


	return 0;
}