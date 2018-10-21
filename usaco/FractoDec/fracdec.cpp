/*
ID: silxikys
PROG: fracdec
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


unsigned GetNumberOfDigits (unsigned i)
{
    return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}

int main() {
	t1 = gettime();
	ofstream fout("fracdec.out");
	ifstream fin("fracdec.in");

	int N, D; fin >> N >> D;
	//calculate number of fives and twos in denominator
	int E = D;
	int num5 = 0, num2 = 0;
	while (E % 5 == 0) {
		E /= 5;
		num5++;
	}
	while (E % 2 == 0) {
		E /= 2;
		num2++;
	}
	int W = max(num5,num2);
	int numChars = 0;
	//integer part
	int integer = N/D;
	N -= D*integer;
	//cout << integer << ".";
	fout << integer << ".";
	numChars += 1 + GetNumberOfDigits(integer);
	//non-repeating part
	if (N == 0) {
		//cout << 0 << endl;
		fout << 0 << endl;
	}
	else {
		int nextDigit;
		for (int i = 0; i < W; i++) {
			N *= 10;
			nextDigit = N/D;
			//cout << nextDigit;
			fout << nextDigit;
			numChars++;
			N -= nextDigit*D;
		}
		//recurring part
		if (N != 0) {
		//cout << "(";
		fout << "(";
		numChars++;

		int firstRemainder = 0;
		bool flag = true;
		while (N != 0 && flag == true) {
			//checks to make sure N is not in remainders before adding N to the vector
			if (firstRemainder == 0) firstRemainder = N;
			else if (N == firstRemainder) break;

			if (flag == true) {
				N *= 10;
				nextDigit = N/D;
				N -= nextDigit*D;
				if (numChars == 76) {
					
					//cout << "\n" << nextDigit;
					fout << "\n" << nextDigit;
					numChars = 1;
				}
				else {
					//cout << nextDigit;
					fout << nextDigit;
					numChars++;
				}
			}
		}
		//cout << ")" << endl;
		fout << ")" << endl;
		}
		else {
			//cout << endl;
			fout << endl;
		}

	}


	
	endProgram(t1);
	return 0;
}