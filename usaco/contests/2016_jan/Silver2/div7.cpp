/*
ID: silxikys
PROG: div7
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

ofstream fout("div7.out");
ifstream fin("div7.in");

const int maxn = 50000;
int cows[maxn];
int N;

int main() 
{
	fin >> N;
	for (int i = 0; i < N; i++) {
		int a; fin >> a;
		a = a % 7;
		if (i == 0) {
			cows[i] = a;
		}
		else {
			cows[i] = (cows[i-1] + a) % 7;
		}
	}
	int first7[7];
	int last7[7];
	for (int i = 0; i < 7; i++) {
		first7[i] = -1;
		last7[i] = -1;
	}

	int found = 0;
	for (int i = 0; i < N && found < 7; i++) {
		int a = cows[i];
		if (first7[a] == -1) {
			first7[a] = i;
			found++;
		}
	}
	found = 0;
	for (int i = N - 1; i >= 0 && found < 7; i--) {
		int a = cows[i];
		if (last7[a] == -1) {
			last7[a] = i;
			found++;
		}
	}
	/*
	for (int i = 0; i < 7; i++) {
		cout << i << ": " << first7[i] << ' ' << last7[i] << '\n';	
	}
	*/
	int ans = 0;
	for (int i = 0; i < 7; i++) {
		if (first7[i] != -1 && last7[i] != -1) {
			int poss = last7[i]-first7[i];
			ans = max(ans,poss);
		}
	}

	cout << ans << '\n';
	fout << ans << '\n';



	return 0;
}
















































