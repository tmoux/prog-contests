/*
ID: silxikys
PROG: measurement
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <sstream>
using namespace std;

ofstream fout("measurement.out");
ifstream fin("measurement.in");

int cows[3];

string findMax(int cows[]) {
	if (cows[0] > cows[1] && cows[0] > cows[2]) {return "B";}
	if (cows[1] > cows[0] && cows[1] > cows[2]) {return "E";}
	if (cows[2] > cows[0] && cows[2] > cows[1]) return "M";
	if (cows[0] == cows[1] && cows[0] > cows[2]) return "BE";
	if (cows[1] == cows[2] && cows[1] > cows[0]) return "EM";
	if (cows[0] == cows[2] && cows[0] > cows[1]) return "BM";
	if (cows[0] == cows[1] && cows[1] == cows[2]) return "BEM";
}

struct Entry {
	int day;
	string cow;
	int change;
};

Entry entries[100];
int N;

int main() 
{
	for (int i = 0; i < 3; i++) {
		cows[i] = 7;
	}
	fin >> N;
	for (int i = 0; i < N; i++) {
		int day;
		string cow;
		string changestring;
		int change;
		int mult = 1;
		fin >> day >> cow >> changestring;
		stringstream str(changestring.substr(1));
		if (changestring[0] == '-') {
			mult = -1;
		}
		str >> change;
		change *= mult;
		entries[i] = {day, cow, change};
	}

	sort(entries,entries+N,[](const Entry& left, const Entry& right) {
		return left.day < right.day;
	});

	for (int i = 0; i < N; i++) {
		cout << entries[i].day << ' ' << entries[i].cow << ' ' << entries[i].change << '\n';
	}

	string currmax = findMax(cows);
	int numchange = 0;
	for (int i = 0; i < N; i++) {
		Entry e = entries[i];
		if (e.cow == "Bessie") {
			cows[0] += e.change;
		}
		else if (e.cow == "Elsie") {
			cows[1] += e.change;
		}
		else if (e.cow == "Mildred") {
			cows[2] += e.change;
		}
	
		if (findMax(cows) != currmax) {
			numchange++;
			currmax = findMax(cows);
		}
	}

	cout << numchange << '\n';
	fout << numchange << '\n';

	return 0;
}