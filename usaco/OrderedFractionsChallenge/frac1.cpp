/*
ID: silxikys
PROG: frac1
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

class Fraction {
	public:
		int n;
		int d;
		double value;
		Fraction() {
			n = 1; d = 1; value = 1; 
		}
		Fraction(int numerator, int denominator) {
			n = numerator;
			d = denominator;
			value = (double) n / d;
		}
		bool isReduced() {
			if (n==1) {
				return true;
			}
			for (int i = 2; i<=n;i++) {
				if (n % i == 0 && d % i == 0) {
					return false;
				}
			}
			return true;
		}

};


int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	ofstream fout("frac1.out");
	ifstream fin("frac1.in");
	int N; fin >> N;


	vector<Fraction> fractions;
	fractions.push_back(Fraction(0,1));
	for (int denom = 1; denom <= N; denom++) {
		for (int numer = 1; numer <= denom; numer++) {
			Fraction f = Fraction(numer,denom);
			if (f.isReduced()) {
				//cout << f.n << "/" << f.d << endl;
				for (int i = fractions.size();i>=0;i--) {
					if (f.value > fractions[i-1].value) {
						fractions.insert(fractions.begin()+i,f);
						break;
					}
				}
				
			}
		}
	}
	for (int i = 0; i<fractions.size();i++) {
		cout << fractions[i].n << "/" << fractions[i].d << endl;
		fout << fractions[i].n << "/" << fractions[i].d << endl;
	}
	
	
	fin.close();
	fout.close();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2-t1).count()/1000000000.0;
	cout << endl << "Execution time: " << duration << " seconds" << endl;
	return 0;
}