/*
ID: silxikys
PROG: cbarn
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

ofstream fout("cbarn.out");
ifstream fin("cbarn.in");

const int maxn = 1000;
int n;
bool filled[maxn];
pair<int,int> cows[maxn];

int dist2(int start, int end) {
	if (end < start) {
		end += n;
	}
	return (end-start)*(end-start);
}

int main() 
{
	fin >> n;
	for (int i = 0; i < n; i++) {
		int num; fin >> num;
		cows[i] = make_pair(i,num);
	}
	/*
	for (int i = 0; i < n; i++) {
		cout << cows[i].first << ' ' << cows[i].second << '\n';
	}
	*/

	int energy = 0;
	int numFilled = 0;
	while (numFilled != n) {
		//cout << numFilled << '\n';
		/*
		for (int i = 0; i < n; i++) {
			cout << cows[i].first << ' ' << cows[i].second << '\n';
		} cout << '\n';
		*/
		pair<int,int> first = cows[0];
		for (int i = n - 1; i >= 0; i--) {
			pair<int,int> p;
			if (i != 0) {
				p = cows[i];
				
			}
			else {
				p = first;
			}
			if (p.second > 0) {
				if (!filled[i]) {
					filled[i] = true;
					p.second--;
					numFilled++;
					energy += dist2(p.first,i);
				}
			}
			cows[(i+1) % n] = p;			
		}
		cout << energy << '\n';
	}

	cout << energy << '\n';
	fout << energy << '\n';


	return 0;
}