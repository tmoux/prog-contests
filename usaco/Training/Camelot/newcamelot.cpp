/*
ID: silxikys
PROG: camelot
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
#include <cstring>
using namespace std;
using namespace std::chrono;

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1;

const int maxrow = 30;
const int maxcol = 26;
const pair<int, int> knightmoves[8] = {{2,1},{1,2},{-2,1},{1,-2},{2,-1},{-1,2},{-2,-1},{-1,-2}};
const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int rows, cols;
int sp[maxrow][maxcol];
pair<int,int> kingpos;
vector<pair<int,int>> knightpos;

void fillsp(int goalrow, int goalcol) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			sp[i][j] = 99999;
		}
	}
	deque<pair<int,int>> deq;
	deq.push_back(make_pair(goalrow, goalcol));
	sp[goalrow][goalcol] = 0;
	while (deq.size() != 0) {
		pair<int, int> q = deq.front();
		for (int i = 0; i < 8; i++) {
			pair<int, int> p = knightmoves[i];
			int newrow = q.first + p.first;
			int newcol = q.second + p.second;
			if (newrow >= 0 && newcol >= 0 && newrow < rows && newcol < cols && sp[newrow][newcol] == 99999) {
				deq.push_back(make_pair(newrow, newcol));
				sp[newrow][newcol] = sp[q.first][q.second] + 1;
			}
		}
		deq.pop_front();
	}
}

vector<pair<int,int>> findpickup() {
	vector<pair<int,int>> ret;
	deque<pair<int,int>> deq;
	for (int i = 0; i < knightpos.size(); i++) {
		pair<int,int> p = knightpos[i];
		deq.push_back(p);
		while (deq.size() != 0) {
			pair<int, int> q = deq.front();
			if (find(ret.begin(),ret.end(),make_pair(q.first,q.second)) == ret.end()) {
				ret.push_back(q);
				for (int i = 0; i < 8; i++) {
					pair<int, int> r = knightmoves[i];
					int newrow = q.first + r.first;
					int newcol = q.second + r.second;
					if (newrow >= 0 && newcol >= 0 && newrow < rows && newcol < cols && sp[newrow][newcol] == sp[q.first][q.second]-1) {
						deq.push_back(make_pair(newrow,newcol));
						
					}
				}
			}

			deq.pop_front();
		}
	}
	return ret;
}

vector<pair<int,int>> newfindpickup() {
	vector<pair<int,int>> ret;
	deque<pair<int,int>> deq;
	int newrow, newcol;
	for (pair<int,int> p : knightpos) {
		deq.push_back(p);
		ret.push_back(p);
	}
	if (ret.size() == rows*cols) {
		return ret;
	}
	while (deq.size() != 0) {
		pair<int,int> q = deq.front();
		for (int i = 0; i < 8; i++) {
			pair<int,int> r = knightmoves[i];
			newrow = q.first + r.first;
			newcol = q.second + r.second;
			if (newrow >= 0 && newcol >= 0 && newrow < rows && newcol < cols && sp[newrow][newcol] < sp[q.first][q.second] && find(ret.begin(),ret.end(),make_pair(newrow,newcol)) == ret.end()) {
				deq.push_back(make_pair(newrow,newcol));
				ret.push_back(make_pair(newrow,newcol));
			}
		}
		deq.pop_front();
	}
	return ret;
}

void printsp() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << sp[i][j] << " ";
		}
		cout << endl;
	}

}

int main() {
	t1 = gettime();
	ofstream fout("camelot.out");
	ifstream fin("camelot.in");

	//input
	fin >> rows >> cols;
	string p; int q, r;
	fin >> p >> q;
	r = alphabet.find(p);
	kingpos = make_pair(q-1,r);
	while (fin >> p >> q) {
		r = alphabet.find(p);
		knightpos.push_back(make_pair(q-1,r));
	}
	/*
	cout << kingpos.first << " " << kingpos.second << endl;
	
	for (pair<int,int> p: knightpos) {
		cout << p.first << " " << p.second << endl;
	}
	*/

	
	//try every possible square
	int mindistance = 99999;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int dist = 0;
			fillsp(i,j);
			//printsp();
			
			vector<pair<int,int>> pickups;
			pickups = newfindpickup();

			if (pickups.size() == 0) {
				pickups.push_back(make_pair(i,j));
			}

			for (pair<int,int> p : knightpos) {
				dist += sp[p.first][p.second];
			}

			//find king distance
			int kingdist = 99999;
			for (pair<int,int> p : pickups) {
				int rowdist = abs(p.first-kingpos.first);
				int coldist = abs(p.second-kingpos.second);
				kingdist = min(kingdist, max(rowdist,coldist));
			}
			dist += kingdist;

			//cout << i << " " << j << " " << dist << endl;
			mindistance = min(mindistance,dist);
			

		}
	}


	cout << mindistance << endl;

	fout << mindistance << endl;
	
	


	
	endProgram(t1);
	return 0;
}