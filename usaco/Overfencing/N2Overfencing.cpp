/*
ID: silxikys
PROG: maze1
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

const int MAX_W = 38, MAX_H = 100;

struct Point{
	int row;
	int col;
};


int W, H;
int sp[MAX_H][MAX_W];
string board[MAX_H*2+1];
vector<Point> adjacents[MAX_H][MAX_W]; 

bool visited[MAX_H][MAX_W];



int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	ofstream fout("maze1.out");
	ifstream fin("maze1.in");

	//inputs
	fin >> W >> H;
	string line;
	getline(fin,line);
	for (int row = 0; row < H*2+1 ;row++) {
		getline(fin, line);
		board[row] = line;
		for (int col = 0; col < W*2+1;col++) {
			if (board[row][col] == ' ' && (row == 0 || row == H*2 || col == 0 || col == W*2)) {
				board[row][col] = '@';
			}
		}	
	}

	for (int row = 0; row < H*2+1;row++) {
		for (int col = 0; col < W*2+1; col++) {
			cout << board[row][col];
		}
		cout << endl;
	}

	//initialize sp and visited
	for (int i = 0; i< MAX_H; i++) {
		for (int j = 0; j< MAX_W; j++) {
			sp[i][j] = 0;
			visited[i][j] = false;
		}
	}


	int endpoints[2][2];
	int endIndex = 0;
	
	//calculate adjacents
	for (int row = 0; row < H;row++) {
		for (int col = 0; col < W; col++) {
			int boardRow = row*2+1, boardCol = col*2+1; 
			if (board[boardRow-1][boardCol] == ' ') {
				Point p = {row-1,col};
				adjacents[row][col].push_back(p);
			}
			if (board[boardRow][boardCol+1] == ' ') {
				Point p = {row, col+1};
				adjacents[row][col].push_back(p);
			}
			if (board[boardRow+1][boardCol] == ' ') {
				Point p = {row+1, col};
				adjacents[row][col].push_back(p);
			}
			
			if (board[boardRow][boardCol-1] == ' ') {
				Point p = {row, col-1};
				adjacents[row][col].push_back(p);
			}
			if (board[boardRow-1][boardCol] == '@' || board[boardRow+1][boardCol] == '@' || board[boardRow][boardCol-1] == '@' || board[boardRow][boardCol+1] == '@') {
				sp[row][col] = 1;

				endpoints[endIndex][0] = row;
				endpoints[endIndex][1] = col;
				endIndex++;
			}
		}
	}

	for (int i = 0; i<endIndex;i++) {
		Point p = {endpoints[i][0], endpoints[i][1]};
		if (i == 1) {
			for (int row = 0; row < MAX_H;row++) {
				for (int col = 0; col < MAX_W;col++) {
					visited[row][col] = false;
				}
			}
		}
		visited[p.row][p.col] = true;
		if (i == 0 && endIndex == 2) {
			visited[endpoints[1][0]][endpoints[1][1]] = true;
		}
		else if (i == 1) {
			visited[endpoints[0][0]][endpoints[0][1]] = true;
		}
		vector<Point> queue;
		for (Point j : adjacents[p.row][p.col]) {
			if ((visited[j.row][j.col] == false && sp[j.row][j.col] == 0) || sp[j.row][j.col] > sp[p.row][p.col] + 1) {
				queue.push_back(j);
				sp[j.row][j.col] = sp[p.row][p.col] + 1;
			}
		}
		while (queue.size() > 0) {
			vector<Point> newq;
			for (Point j : queue) {
				visited[j.row][j.col] = true;
				for (Point k : adjacents[j.row][j.col]) {
					if ((visited[k.row][k.col] == false && sp[k.row][k.col] == 0) || sp[k.row][k.col] > sp[j.row][j.col] + 1) {
						newq.push_back(k);
						sp[k.row][k.col] = sp[j.row][j.col] + 1;
					}
				}
			}
			queue = newq;
		}
	}

	int max = 0;
	for (int i = 0; i<H;i++) {
		for (int j = 0; j<W;j++) {
			int s = sp[i][j];
			cout << s << " ";
			if (s > max) {
				max = s;
			}
		}
		cout << endl;
	}

	cout << max << endl;
	fout << max << endl;






	fin.close();
	fout.close();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2-t1).count()/1000000000.0;
	cout << endl << "Execution time: " << duration << " seconds" << endl;
	return 0;
}