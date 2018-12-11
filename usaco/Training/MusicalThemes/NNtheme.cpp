/*
ID: silxikys
PROG: theme
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <climits>
#include <array>
#include <chrono>
#include <math.h>
using namespace std;
using namespace std::chrono;

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1;

int N;
const int maxn = 5000;
const int p = 781250;
int notes[maxn];

struct packArray {
	unsigned int arr[p];

	bool get(int i, int j) {
		int index = i * maxn + j;
		int prow = index/32;
		int rem = index % 32;
		unsigned int pack = arr[prow];
		return ((pack >> rem) & 1);
	}

	void flip(int i, int j) {
		int index = i * maxn + j;
		int prow = index / 32;
		int rem = index % 32;
		unsigned int pack = arr[prow];
		unsigned int add = 1;
		add <<= rem;
		pack ^= add;
		arr[prow] = pack;
	}
};

vector<int> themes[5005];

int main() {
	t1 = gettime();
	ofstream fout("theme.out");
	ifstream fin("theme.in");

	//input
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> notes[i];
	}


	//create the themes for length 5
	int longtheme = 0;
	for (int i = 0; i < N - 5; i++) {
		for (int j = i + 5; j < N; j++) {
			if (j + 5 <= N) {
				if (notes[i+1]-notes[i]   == notes[j+1]-notes[j]   &&
					notes[i+2]-notes[i+1] == notes[j+2]-notes[j+1] &&
					notes[i+3]-notes[i+2] == notes[j+3]-notes[j+2] &&
					notes[i+4]-notes[i+3] == notes[j+4]-notes[j+3]) {
					themes[i].push_back(j);
					longtheme = 5;
				}
			}
		}
	}
	/*
	int counter = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (themes.get(i,j)) {
				counter++;
			}
		} 
	}
	*/
	
	for (int length = 6; length < N / 2 + 1; length++) {
		bool streak = false;
		//cout << length << "-----" << endl;
		for (int i = 0; i < N ; i++) {
			for (int a = 0; a < themes[i].size(); a++) {
				int j = themes[i][a];
				//cout << i << " " << j << endl;
				if (j + length <= N && j >= i + length - 1 &&
				notes[i+length-1]-notes[i+length-2]==
				notes[j+length-1]-notes[j+length-2]) {
					streak = true;
				}
				else {
					themes[i].erase(themes[i].begin()+a);	
				}
			}
		}
		if (streak) {
			longtheme = length;
		}
		else {
			break;
		}
	}

	

	cout << longtheme << endl;
	fout << longtheme << endl;

	

	endProgram(t1);
	return 0;
	
	
}