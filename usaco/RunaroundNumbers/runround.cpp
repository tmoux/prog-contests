/*
ID: silxikys
PROG: runround
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

int digitAtIndex(int n, int length, int index) {
	return (int)(n/pow(10,length-index-1)) % 10;
}

bool isRunround(int n) {
	int numOfDigits = ceil(log10(n+1));
	vector<int> usedDigits(numOfDigits,0);

	//check that digits are unique and none are 0
	array<int,10> digits; digits.fill(0);
	int d = n;
	while (d > 0) {
		int a = d % 10;
		if (a == 0) return false;
		if (digits[a] == 1) return false;
		digits[a] = 1;
		d /= 10;
	}	
	//check that number is runaround number
	int oldDigitIndex = 0;
	do {
		if (usedDigits[oldDigitIndex] != 0) {
			return false;
		}
		int oldDigit = digitAtIndex(n,numOfDigits,oldDigitIndex);
		usedDigits[oldDigitIndex] = 1;
		int newDigitIndex = (oldDigitIndex + oldDigit) % numOfDigits;
		//cout << oldDigitIndex << " " << oldDigit << endl << newDigitIndex << endl << endl;
		
		oldDigitIndex = newDigitIndex;
	} while (oldDigitIndex != 0);
	for (int i = 0; i < usedDigits.size();i++) {
		if (usedDigits[i] == 0) return false;
	}
	return true;

}

int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	ofstream fout("runround.out");
	ifstream fin("runround.in");
	
	int M; fin >> M;

	

	//cout << isRunround(147) << endl;

	
	unsigned int x = M+1;
	while (!isRunround(x)) x++;

	//output
	cout << x << endl;
	fout << x << endl;
	

	fin.close();
	fout.close();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2-t1).count()/1000000000.0;
	cout << endl << "Execution time: " << duration << " seconds" << endl;
	return 0;
}