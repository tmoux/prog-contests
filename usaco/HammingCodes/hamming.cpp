/*
ID: silxikys
PROG: hamming
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

int hamming(unsigned int x, unsigned int y) {
	unsigned int z = x^y;
	int count = 0;
	while (z) {
		if (z&1) {
			count++;
		}
		z >>= 1;
	}
	return count;
}

int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	ofstream fout("hamming.out");
	ifstream fin("hamming.in");
	
	int N, B, D; fin >> N >> B >> D;
	int codewords[64] = {0};
	int index = 1;

	for (int num = 1; num < pow(2,B);num++) {
		bool flag = true;
		for (int i = 0; i<index;i++) {
			//cout << num << " " << codewords[i] << " " << hamming(num,codewords[i]) << endl;
			if (hamming(num,codewords[i]) < D) {
				flag = false;
				break;
			}
		}
		if (flag) {
			codewords[index] = num;
			index++;
			if (index >= N) {
				break;
			}
		}
	}

	//output
	for (int i = 0; i<index;i++) {
		cout << codewords[i] << " ";
	}

	for (int i = 0; i<index;i++) {
		if (i % 10 == 9 || i == index-1) {
			fout << codewords[i] << endl;
		} 
		else {
			fout << codewords[i] << " ";
		}
	}
	
	fin.close();
	fout.close();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2-t1).count()/1000000000.0;
	cout << endl << "Execution time: " << duration << " seconds" << endl;
	return 0;
}