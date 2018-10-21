/*
ID: silxikys
PROG: hayfeast
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <math.h>
using namespace std;

ofstream fout("hayfeast.out");
ifstream fin("7.in");

struct Haybale
{
	int flavor;
	int spicy;
};
const int maxn = 100001;
Haybale haybales[maxn];
int N;
long M;


int main() 
{
	fin >> N >> M;
	for (int i = 0; i < N; i++) {
		int f, s;
		fin >> f >> s;
		haybales[i] = {f,s};
	}
	int left = 0;
	set<int> spices;
	long currFlavor = 0;
	int minSpicy = 2000000000;
	for (int i = 0; i < N; i++) {
		currFlavor += haybales[i].flavor;
		spices.insert(haybales[i].spicy);
		while (currFlavor - haybales[left].flavor >= M) {
			currFlavor -= haybales[left].flavor;
			spices.erase(haybales[left].spicy);
			left++;
		}
		if (currFlavor >= M) {
			minSpicy = min(minSpicy,*spices.rbegin());
		}
	}

	cout << minSpicy << '\n';
	fout << minSpicy << '\n';

	return 0;
}