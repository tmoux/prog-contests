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

const int maxn = 100000;

struct Entry 
{
	int day;
	string id;
	int change;
};

Entry entries[maxn];

int N, G;
map<string,int> cows;

int main() 
{
	fin >> N >> G;
	int currmax = G;
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
	/*
	for (int i = 0; i < N; i++) {
		Entry e = entries[i];
		cout << e.day << ' ' << e.id << ' ' << e.change << '\n';
	}
	*/
	map<int,int> maxes;
	maxes[G] = 1000000000;
	int numChange = 0;
	for (int i = 0; i < N; i++) {
		Entry e = entries[i];
		if (cows.count(e.id) == 0) {
			cows[e.id] = G;
		}

		map<int,int>::reverse_iterator it = maxes.rbegin();
		++it;
		int secondbiggest = it->first;
		if (cows[e.id] == currmax) {
			if (maxes[cows[e.id]] != 1) {
				numChange++;
			}
			else if (cows[e.id] + e.change > currmax && cows[e.id] == G) {
				numChange++;
			}
			else if (cows[e.id] + e.change <= secondbiggest) {
				numChange++; 
			}
		}
		else if (cows[e.id] < currmax && cows[e.id] + e.change >= currmax) {
			numChange++;
		}
		else if (cows[e.id] > currmax && cows[e.id] + e.change <= secondbiggest) {
			numChange++;
		}

		maxes[cows[e.id]]--;
		cows[e.id] += e.change;
		maxes[cows[e.id]]++;

		if (currmax < cows[e.id]) {
			currmax = cows[e.id];
		}
		else if (maxes[currmax] == 0) {
			maxes.erase(currmax);
			currmax = maxes.rbegin()->first;
		}

	}





	cout << numChange << '\n';
	fout << numChange << '\n';
	
	
	

	return 0;
}