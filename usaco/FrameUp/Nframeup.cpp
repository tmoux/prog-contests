/*
ID: silxikys
PROG: frameup
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

const int maxsize = 30;
struct Letter {
	int maxx = 0, maxy = 0;
	int miny = maxsize + 2, minx = maxsize + 2;
};

int H, W;
Letter llist[26];
int maxletter = 0;
char board[maxsize][maxsize];
int dag[maxsize][maxsize];
vector<string> solutions;

bool isletter(char c) {
	return (int(c) >= 65 && int(c) <= 90);
}
int charToInt(char c) {
	return (int(c) - 65);
}
char intToChar(int i) {
	return char(i + 65);
}

void findSorts(string sofar) {
	if (sofar.length() == maxletter+1) {
		solutions.push_back(sofar);
		cout << sofar << '\n';
		return;
	}
	for (int i = 0; i <= maxletter; i++) {
		char let = intToChar(i);

		bool canAdd = true;
		for (char c: sofar) {
			int k = charToInt(c);
			if (dag[k][i] == 1) {
				canAdd = false;
				break;
			}
		}
		if (canAdd) {
			findSorts(sofar+let);
		}
	}
}

void newFindSorts(string sofar) {
	//cout << sofar << endl;
	if (sofar.length() == maxletter+1) {
		solutions.push_back(sofar);
		return;
	}
	for (int i = 0; i <= maxletter; i++) {
		if (sofar.find(intToChar(i)) == string::npos) { //if the letter is not already in the string
			char let = intToChar(i);
			bool canAdd = true;
			for (int j = 0; j <= maxletter; j++) {
				if (dag[i][j] && sofar.find(intToChar(j)) == string::npos) {
					//if j must come before i, and j is NOT found in the string sofar
					canAdd = false;
					break;
				}
			}
			if (canAdd) {
				//this means that all of the frames that must come before i are already in sofar
				newFindSorts(sofar+let);
			}
		}
	}
}
map<char,char> mapping;
map<char, char> reversemap;

int main() {
	t1 = gettime();
	ofstream fout("frameup.out");
	ifstream fin("frameup.in");

	fin >> H >> W;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			char c; fin >> c;
			board[i][j] = c;
			if (isletter(c)) {
				if (mapping.find(c) == mapping.end()) {
					mapping[c] = intToChar(maxletter);
					reversemap[intToChar(maxletter)] = c;
					maxletter++;
				}
				c = mapping[c];
				board[i][j] = c;
				int a = charToInt(c);
				
				if (j < llist[a].minx) {
					llist[a].minx = j;
				}
				if (j > llist[a].maxx) {
					llist[a].maxx = j;
				}
				if (i < llist[a].miny) {
					llist[a].miny = i;
				}
				if (i > llist[a].maxy) {
					llist[a].maxy = i;
				}

			}
		}
	}
	maxletter--;
	/* prints letters
	for (int i = 0; i <= maxletter; i++) {
		cout << intToChar(i) << '\n';
		Letter a = llist[i];
		cout << a.minx << " " << a.maxx << " " << a.miny << " " << a.maxy << '\n';
	}
	*/
	//doing "lazy edge transversal" (which sounds way more complex than it is)
	//this creates the DAG
	for (int k = 0; k <= maxletter; k++) {
		char let = intToChar(k);
		Letter l = llist[k];
		for (int i = l.miny; i <= l.maxy; i++) {
			for (int j = l.minx; j <= l.maxx; j++) {
				if (i == l.miny || i == l.maxy || j == l.minx || j == l.maxx) {
					//if (i,j) is on the border of the frame
					if (board[i][j] != let) {
						int child = charToInt(board[i][j]);
						dag[child][k] = 1;
					}
				}
			}
		}
	}
	
	//prints DAG
	/*
	for (int i = 0; i <= maxletter; i++) {
		for (int j = 0; j <= maxletter; j++) {
			cout << dag[i][j] << ' ';
		} cout << '\n';
	}
	*/	

	//generate all possible sorts
	//findSorts("");
	newFindSorts("");
	//output
	vector<string> output;
	for (string s: solutions) {
		string add;
		for (char c: s) {
			add += reversemap[c];
		}
		output.push_back(add);
	}
	sort(output.begin(),output.end());
	cout << solutions.size() << '\n';
	for (string s : output) {
		//cout << s << '\n';
		fout << s << '\n';
	}


	
	endProgram(t1);
	return 0;
}