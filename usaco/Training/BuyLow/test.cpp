/*
ID: silxikys
PROG: buylow
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


struct bignum {
	vector<int> digits; //digits stored in reverse order

	bignum add(bignum b) {
		bignum ret;
		int carry = 0;
		for (int pos = 0; pos < max(digits.size(), b.digits.size()) + 1; pos++) {
			int d1 = 0, d2 = 0;
			if (pos < digits.size()) {
				d1 = digits[pos];
			}
			if (pos < b.digits.size()) {
				d2 = b.digits[pos];
			}
			int s = d1 + d2 + carry;
			carry = s / 10;
			ret.digits.push_back(s % 10);
		}
		return ret;
	}
	string print() {
		string ret;
		for (int i = digits.size() -1; i >= 0; i--) {
			if (digits[i] != 0) {
				for (int j = i; j >= 0; j--) {
					char ch = digits[j] + '0';
					ret = ret + ch;
				}
				break;
			}
		}
		return ret;
	}
};

const int maxn = 5005;
int prices[maxn];
pair<int,bignum> most[maxn];



bignum makebignum(int n) {
	bignum ret;
	while (n > 0) {
		ret.digits.push_back(n % 10);
		n /= 10;
	}
	return ret;
}

int main() {
	
	cout << 5.0/0 << endl;
	return 0;
}