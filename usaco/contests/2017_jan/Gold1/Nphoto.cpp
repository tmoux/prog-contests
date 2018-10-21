/*
ID: silxikys
PROG: bphoto
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
using namespace std;

ofstream fout("bphoto.out");
ifstream fin("bphoto.in");

vector<int> lefts, rights;
const int maxn = 100000;
int cows[maxn];
int N;

int binSearch(const vector<int>& arr, int i, int l, int r) {
	if (l <= r) {
		int mid = (r + l)/2;
		if (arr[mid] == i) {
			return mid;
		}
		if (arr[mid] < i) {
			return binSearch(arr,i,mid+1,r);
		}
		return binSearch(arr,i,l,mid-1);
	}
	return -1;
}

int main() 
{
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> cows[i];
		rights.push_back(cows[i]);
	}

	sort(rights.begin(),rights.end());

	int numUnbalanced = 0;
	for (int i = 0; i < N; i++) {
		rights.erase(find(rights.begin(),rights.end(),cows[i]));
		/*
		for (int j: rights) {
			cout << j << ' ';
		} cout << '\n';

		for (int j: lefts) {
			cout << j << ' ';
		} cout << '\n';
		*/

		int numr = rights.end() - upper_bound(rights.begin(),rights.end(),cows[i]);
		int numl = lefts.end() - upper_bound(lefts.begin(),lefts.end(),cows[i]);

		//cout << cows[i] << ' ' << numl << ' ' << numr << '\n';
		if (numr * 2 < numl || numl * 2 < numr) {
			numUnbalanced++;
		}


		lefts.insert(upper_bound(lefts.begin(),lefts.end(),cows[i]),cows[i]);
	}

	cout << numUnbalanced << '\n';
	fout << numUnbalanced << '\n';

	return 0;
}