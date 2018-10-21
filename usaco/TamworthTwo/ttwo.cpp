/*
ID: silxikys
PROG: ttwo
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

char board[10][10];

struct Pos{
	int row;
	int col;
	int ori;
	char name;
};




int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	ofstream fout("ttwo.out");
	ifstream fin("ttwo.in");

	Pos F, C;
	Pos ps[2] = {F,C};

	//read input
	for (int row = 0; row < 10;row++) {
		for (int col = 0; col < 10; col++) {
			fin >> board[row][col];
			if (board[row][col] == 'F') {
				F = {row, col, 0, 'F'};
			}
			else if (board[row][col] == 'C') {
				C = {row, col, 0, 'C'};
			}
		}
	}
	/*
	for (int row = 0; row < 10; row++) {
		for (int col = 0; col < 10; col++) {
			cout << board[row][col];
		}
		cout << endl;
	}
	*/
	bool found = false;
	for (int i = 0; i<146;i++) {
		//farmer F
		int nextRowF = F.row, nextColF = F.col;

		switch(F.ori) {
			case 0: nextRowF--; break;
			case 1: nextColF++; break;
			case 2: nextRowF++; break;
			case 3: nextColF--; break;
		}
		//cout << nextRowF << " " << nextColF << endl;
		if (nextRowF >= 0 && nextRowF <= 9 && nextColF >= 0 && nextColF <=9 && board[nextRowF][nextColF] == '.') {
			board[F.row][F.col] = '.';
			F.row = nextRowF;
			F.col = nextColF;
			board[F.row][F.col] = F.name;
		}
		else {
			F.ori = (F.ori + 1) % 4;
		}
		//cout << F.name << " " << F.row << " " << F.col << " " << F.ori << endl;

		//cow C
		int nextRowC = C.row, nextColC = C.col;

		switch(C.ori) {
			case 0: nextRowC--; break;
			case 1: nextColC++; break;
			case 2: nextRowC++; break;
			case 3: nextColC--; break;
		}
		if (nextRowC >= 0 && nextRowC <= 9 && nextColC >= 0 && nextColC <=9 && board[nextRowC][nextColC] != '*') {
			board[C.row][C.col] = '.';
			C.row = nextRowC;
			C.col = nextColC;
			board[C.row][C.col] = C.name;
		}
		else {
			C.ori = (C.ori + 1) % 4;
		}
		//cout << C.name << " " << C.row << " " << C.col << " " << C.ori << endl;

	if (F.row == C.row && F.col == C.col) {
		cout << i + 1 << " minutes" << endl;
		fout << i + 1 << endl;
		found = true;
		break;
		
	}

	}

	if (found == false) {
		fout << 0 << endl;
		cout << 0 << endl;
	}
	
	
	
	
	fin.close();
	fout.close();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2-t1).count()/1000000000.0;
	cout << endl << "Execution time: " << duration << " seconds" << endl;
	return 0;
}