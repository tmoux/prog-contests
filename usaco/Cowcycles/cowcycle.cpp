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

pvd getDiffs(const vector<int>& fronts, const vector<int>& rears) {
	vector<double> gears;
	for (int i: fronts) {
		for (int j: rears) {
			gears.push_back((double)i/(double)j);
		}
	}
	sort(gears.begin(),gears.end());
	vector<double> diffs;
	for (int i = 0; i < gears.size() - 1; i++) {
		diffs.push_back(gears[i+1]-gears[i]);
	}
	return {diffs,mean(diffs)};
}

double getVariance(const vector<int>& fronts, const vector<int>& rears) {
	pvd PVD = getDiffs(fronts,rears);
	return variance(PVD.second,PVD.first);
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
	ifstream fin("8.in");
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
	for (const vector<int>& f: frontCombos) {
		for (const vector<int>& r: rearCombos) {
			double maxRatio = (double)f[f.size()-1]/(double)r[0];
			double minRatio = (double)f[0]/(double)r[r.size()-1];
			if (maxRatio/minRatio >= 3) {
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
	
	//output
	for (int i = 0; i < frontAns.size(); i++) {
		//cout << frontAns[i];
		fout << frontAns[i];
		if (i != frontAns.size()-1) {
			//cout << ' ';
			fout << ' ';
		}
	}
	//cout << '\n';
	fout << '\n';
	for (int i = 0; i < rearAns.size(); i++) {
		//cout << rearAns[i];
		fout << rearAns[i];
		if (i != rearAns.size()-1) {
			//cout << ' ';
			fout << ' ';
		}
	}
	//cout << '\n';
	fout << '\n';
	
	return 0;
}