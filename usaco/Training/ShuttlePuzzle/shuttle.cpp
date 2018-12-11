/*
ID: silxikys
PROG: shuttle
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
#include <deque>
using namespace std;
using namespace std::chrono;

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1;

const int maxh = 26;
map<char,char> complement = {{'w','b'}, {'b','w'}};

struct Board {
	int size;
	char pos[maxh];
	vector<int> path;

	bool canmove(int n) {
		int space;
		for (int i = 1; i <= size; i++) {
			if (pos[i] == ' ') {
				space = i;
				break;
			}
		}
		if (abs(space - n) > 2 || n == space) {
			return false;
		}
		if (abs(space - n) == 2 && pos[(n+space)/2] == complement[pos[n]]) {
			return true;
		}
		if (abs(space - n) == 1) {
			return true;
		}
	}

	Board move(int n) {
		Board ret;
		ret.size = size;
		ret.path = path;
		int space;
		for (int i = 1; i <= size; i++) {
			if (pos[i] == ' ') {
				space = i;
				break;
			}
		}
		for (int i = 1; i <= size; i++) {
			ret.pos[i] = pos[i];
		}
		ret.pos[space] = pos[n];
		ret.pos[n] = ' ';
		return ret;
	}

	bool equals(Board b) {
		for (int i = 1; i <= size; i++) {
			if (pos[i] != b.pos[i]) {
				return false;
			}
		}
		return true;
	}

	void print() {
		for (int i = 1; i <= size; i++) {
			cout << pos[i];
		} cout << endl;
	}
};


int main() {
	t1 = gettime();
	ofstream fout("shuttle.out");
	ifstream fin("shuttle.in");

	int N; fin >> N;
	int numholes = 2*N+1;
	Board start;
	start.size = numholes;
	for (int i = 1; i <= N; i++) {
		start.pos[i] = 'w';
		start.pos[i+N+1] = 'b';
		if (i == N) {
			start.pos[i+1] = ' ';
		}
	}

	//now start board is created
	deque<Board> boards = {start};
	vector<Board> seenboards = {start};
	while (boards.size() != 0) {
		Board first = boards.front();
		for (int i = 1; i <= numholes; i++) {
			if (first.canmove(i)) {
				Board nxt = first.move(i);
				nxt.path.push_back(i);

				bool newboard = true;
				
				for (Board b: seenboards) {
					if (b.equals(nxt)) {
						newboard = false;
						break;
					}
				}

				if (newboard) {
					seenboards.push_back(nxt);
					boards.push_back(nxt);
				}
			}
		}
		boards.pop_front();
	}


	cout << seenboards.size() << '\n';
	/*
	for (Board b: seenboards) {
		b.print();
		for (int i : b.path) {
			cout << i << " ";
		} cout << "\n\n";
	}
	*/



	
	endProgram(t1);
	return 0;
}