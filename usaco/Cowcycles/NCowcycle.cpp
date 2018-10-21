/*
ID: silxikys
PROG: cowcycle
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
typedef pair<vector<double>,double> pvd;

int F, R;
int F1, F2, R1, R2;
vector<vector<int>> frontCombos, rearCombos;

double variance(double mean, const vector<double>& diffs) {
	double sum = 0;
	for (double i: diffs) {
		sum += (i-mean)*(i-mean);
	}
	return sum/diffs.size();
}

double mean(const vector<double>& ratios) {
	double sum = 0;
	for (double i: ratios) {
		sum += i;
	}
	return sum/ratios.size();
}

double gears[100];
double getVariance(const vector<int>& fronts, const vector<int>& rears) {
	int index = 0;
	int numGears = fronts.size()*rears.size();
	for (const int& i: fronts) {
		for (const int& j: rears) {
			gears[index++] = (double)i/j;
		}
	}
	sort(gears,gears+numGears);
	vector<double> diffs(numGears-1);
	index = 0;
	for (int i = 0; i < numGears - 1; i++) {
		diffs[index++] = gears[i+1]-gears[i];
	}
	return variance(mean(diffs),diffs);
}


void getCombinations(const vector<int>& arr, vector<int>& data, int start, int end, int index, int r, bool isFront) {
	if (index == r) {
		if (isFront) {
			frontCombos.push_back(data);
		}
		else {
			rearCombos.push_back(data);
		}
		return;
	}
	for (int i = start; i <= end && end - i + 1 >= r-index; i++) {
		data[index] = arr[i];
		getCombinations(arr,data,i+1,end,index+1,r,isFront);
	}
}

int main() {
	ofstream fout("cowcycle.out");
	ifstream fin("cowcycle.in");
	fin >> F >> R;
	fin >> F1 >> F2 >> R1 >> R2;

	vector<int> frontOptions(F2-F1+1);
	iota(begin(frontOptions),end(frontOptions),F1);
	vector<int> backOptions(R2-R1+1);
	iota(begin(backOptions),end(backOptions),R1);
	//fill fronts
	vector<int> frontVec(F);
	vector<int> backVec(R);
	getCombinations(frontOptions,frontVec,0,frontOptions.size()-1,0,F,1);
	getCombinations(backOptions,backVec,0,backOptions.size()-1,0,R,0);
	
	
	double minVariance = 999999999;
	vector<int> frontAns, rearAns;
	int counter = 0;
	int c1 = 0;
	for (const vector<int>& f: frontCombos) {
		for (const vector<int>& r: rearCombos) {
			c1++;
			int f0 = f[0], fn = f[f.size()-1], r0 = r[0], rn = r[r.size()-1];
			if ((double)(fn*rn)/(r0*f0) >= 3) {
				counter++;
				
				double var = getVariance(f,r);
				if (var < minVariance) {
					//cout << var << '\n';
					minVariance = var;
					frontAns = f;
					rearAns = r;
				}
				
			}
			
		}
	}
	cout << counter << '\n';
	cout << c1 << '\n';
	//output
	for (int i = 0; i < frontAns.size(); i++) {
		cout << frontAns[i];
		fout << frontAns[i];
		if (i != frontAns.size()-1) {
			cout << ' ';
			fout << ' ';
		}
	}
	cout << '\n';
	fout << '\n';
	for (int i = 0; i < rearAns.size(); i++) {
		cout << rearAns[i];
		fout << rearAns[i];
		if (i != rearAns.size()-1) {
			cout << ' ';
			fout << ' ';
		}
	}
	cout << '\n';
	fout << '\n';
	
	return 0;
}