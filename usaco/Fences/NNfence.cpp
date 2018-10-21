/*
ID: silxikys
PROG: fence
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

//globals
int F;
int adjacents[505][505];
int largestVertex = 0;

int countDegree(int i) {
	int ret = 0;
	for (int j = 1; j <= largestVertex; j++) {
		ret += adjacents[i][j];
	}
	return ret;
}

int main() {
	t1 = gettime();
	ofstream fout("fence.out");
	ifstream fin("fence.in");

	fin >> F;
	for (int a = 0; a < F; a++) {
		int i, j; fin >> i >> j;
		adjacents[i][j]++;
		adjacents[j][i]++;

		if (i > largestVertex) {
			largestVertex = i;
		}
		if (j > largestVertex) {
			largestVertex = j;
		}
	}
	/*
	for (int i = 1; i <= largestVertex; i++) {
		for (int j = 1; j <= largestVertex; j++) {
			cout << adjacents[i][j] << " ";
		}
		cout << endl;
	}
	*/
	//find start vertex
	int startVertex = 0;
	for (int i = 1; i <= largestVertex; i++) {
		if (countDegree(i) % 2 == 1) {
			startVertex = i;
			break;
		}
	}
	if (startVertex == 0) {
		startVertex = 1;
	}
	//loop through all vertices, find next vertex
	int currVertex = startVertex;
	cout << currVertex << endl;
	vector<int> fl; fl.push_back(currVertex);
	for (int i = 0; fl.size() < F; i++) {
		//find next vertex
		int nextVertex = 0;
		for (int j = 1; j <= largestVertex; j++) {
			if (adjacents[currVertex][j] > 0 && (countDegree(j) % 2) == 0) {
				nextVertex = j;
				break;
			}
		}
		//cout << nextVertex << endl;
		if (nextVertex == 0) {
			//cout <<i <<endl;
			if (countDegree(currVertex) > 0) {
				for (int j = 1; j <= largestVertex; j++) {
					if (adjacents[currVertex][j] > 0) {
						nextVertex = j;
						break;
					}
				}
			}
			else {
				while (countDegree(fl[fl.size()-2]) == 0) {
					//add back edges
					adjacents[fl[fl.size()-2]][fl.back()]++;
					adjacents[fl.back()][fl[fl.size()-2]]++;
					fl.pop_back();
				}
				currVertex = fl[fl.size()-2];
				for (int j = 1; j <= largestVertex; j++) {
					if (adjacents[currVertex][j] > 0 && (countDegree(j) % 2) == 0) {
						nextVertex = j;
						break;
					}
				}
				adjacents[currVertex][fl.back()]++;
				adjacents[fl.back()][currVertex]++;
				fl.pop_back();
			}
		}

		/*
		cout << "next number: " << nextVertex << endl;
		if (i >= 485) {
			for (int a = 1; a <= largestVertex; a++) {
				if (countDegree(a) > 0) {
					cout << a << ": ";
					for (int b = 1; b <= largestVertex; b++) {
						if (adjacents[a][b] > 0) {
							cout << b << " ";
						}
					}
					cout << endl;
				}
				
			}
			cout << endl;
		}
		*/

		//delete adjacents
		adjacents[currVertex][nextVertex]--;
		adjacents[nextVertex][currVertex]--;

		currVertex = nextVertex;
		fl.push_back(currVertex);

		if (fl.size() == F) {
			break;
		}
	}

	cout << fl.size() << endl;
	/*
	for (int i: fl) {
		cout << i << endl;
		fout << i << endl;
	}
	*/
	

	
	endProgram(t1);
	return 0;
}