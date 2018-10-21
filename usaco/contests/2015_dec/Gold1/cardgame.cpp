/*
ID: silxikys
PROG: cardgame
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <functional>
#include <set>
using namespace std;

ofstream fout("cardgame.out");
ifstream fin("cardgame.in");

const int maxn = 50001;
int N;
set<int> bessie1, bessie2, opp1, opp2;
int main() 
{
	//input
	fin >> N;
	for (int i = 0; i < N; i++) {
		int j; fin >> j;
		if (i < N/2) {
			opp1.insert(j);
		}
		else {
			opp2.insert(j);
		}
	}
	//build sets
	int counter = 2*N;
	while (bessie1.size() != N/2) {
		if (opp1.count(counter) == 0 && opp2.count(counter) == 0) {
			bessie1.insert(counter);
		}
		counter--;
	}
	while (bessie2.size() != N/2) {
		if (opp1.count(counter) == 0 && opp2.count(counter) == 0) {
			bessie2.insert(counter);
		}
		counter--;
	}
	//Greedily count number of winning cards
	int total = 0;
	for (int i: opp1) {
		auto it = bessie1.lower_bound(i);
		if (it != bessie1.end()) {
			total++;
			bessie1.erase(it);
		}
	}
	for (auto rit = opp2.rbegin(); rit != opp2.rend(); ++rit) {
		auto it = bessie2.lower_bound(*rit);
		if (it != bessie2.begin()) {
			it--;
			total++;
			bessie2.erase(it);
		}
	}
	//output
	cout << total << '\n';
	fout << total << '\n';
	return 0;
}