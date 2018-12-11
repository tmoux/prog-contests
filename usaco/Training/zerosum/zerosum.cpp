/*
ID: silxikys
PROG: zerosum
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

vector<vector<char>> chars;
const char operators[] = {' ','+', '-'};

int evaluate(int index) {
	vector<char> ops = chars[index];
	vector<int> numbers = {1};
	for (int i = 0; i<ops.size();i++) {
		if (ops[i] == '+' || ops[i] == '-') {
			numbers.push_back(i+2);
		}
		else {
			numbers[numbers.size()-1] = numbers[numbers.size()-1] * 10 + (i+2);
		}
	}
	int sum = numbers[0];
	int nextIndex = 1;
	for (int i = 0; i<ops.size();i++) {
		if (ops[i] == '+') {
			sum += numbers[nextIndex];
			nextIndex++;
		}
		else if (ops[i] == '-') {
			sum -= numbers[nextIndex];
			nextIndex++;
		}
	}
	/*
	for (int i = 0; i<ops.size();i++) {
		cout << ops[i];
	}
	cout << endl;
	for (int i = 0; i<numbers.size();i++) {
		cout << numbers[i] << " ";
	}
	cout << endl;
	cout << sum << endl; 
	*/
	return sum;
	
}

void buildChars(int n, int depth, vector<char> addArray) {
	if (depth < n-1) {
		for (int i = 0; i < 3; i++) {
			vector<char> newArray = addArray;
			newArray.push_back(operators[i]);
			buildChars(n, depth+1, newArray);
		}
	}
	else {
		chars.push_back(addArray);
	}
}


int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	ofstream fout("zerosum.out");
	ifstream fin("zerosum.in");
	
	int N; fin >> N;

	//generate chars vector
	buildChars(N,0,vector<char> {});

	for (int i = 0; i<chars.size();i++) {
		if (evaluate(i) == 0) {
			cout << 1;
			fout << 1;
			for (int j = 0; j<chars[i].size();j++) {
				cout << chars[i][j];
				cout << j+2;
				fout << chars[i][j];
				fout << j+2;
			}
			cout << endl;
			fout << endl;
		}
	}

	
	
	fin.close();
	fout.close();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2-t1).count()/1000000000.0;
	cout << endl << "Execution time: " << duration << " seconds" << endl;
	return 0;
}