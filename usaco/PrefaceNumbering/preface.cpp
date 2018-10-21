/*
ID: silxikys
PROG: preface
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

const string numerals[7] = {"I","V","X","L","C","D","M"};
const string numeralsDec[4] = {"I","X","C","M"};
map<string,int> numValue; 
	

string greatestNumeral(int n) {

	for (int i = sizeof(numerals)/sizeof(numerals[0])-1; i >= 0; i--) {
		string numeral = numerals[i];
		if (n >= numValue[numeral]) {
			return numeral;
		}
	}
}

string greatestDecNumeral(int n) {
	for (int i = sizeof(numeralsDec)/sizeof(numeralsDec[0])-1; i >= 0; i--) {
		string numeral = numeralsDec[i];
		if (n >= numValue[numeral]) {
			return numeral;
		}
	}
}

string createNumeral(int n, string ret = "") {

	string greatestNum = greatestNumeral(n);
	string greatestDecNum = greatestDecNumeral(n);
	string newGreatestNum = greatestNumeral(n+numValue[greatestDecNum]);
	//cout << greatestNum << " " << greatestDecNum << " " << newGreatestNum << endl; 
	if (greatestNum != newGreatestNum) {
		ret += greatestDecNum + newGreatestNum;
		n -= (numValue[newGreatestNum] - numValue[greatestDecNum]);

	}
	else {
		ret += greatestNum;
		n -= numValue[greatestNum];
	}

	//cout << n << " " << ret << endl;
	if (n == 0) {
		return ret;
	}
	else {
		ret = createNumeral(n, ret);
		return ret;
	}

		
	
	
}

int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	ofstream fout("preface.out");
	ifstream fin("preface.in");

	//initialize numValue map
	numValue["I"] = 1; 
	numValue["V"] = 5; 
	numValue["X"] = 10; 
	numValue["L"] = 50; 
	numValue["C"] = 100; 
	numValue["D"] = 500; 
	numValue["M"] = 1000;
	
	int N; fin >> N;

	map<string, int> countNumerals;
		countNumerals["I"] = 0; 
		countNumerals["V"] = 0; 
		countNumerals["X"] = 0; 
		countNumerals["L"] = 0; 
		countNumerals["C"] = 0; 
		countNumerals["D"] = 0; 
		countNumerals["M"] = 0;

	//cout << createNumeral(3) << endl;

	for (int i = 1; i<= N;i++) {
		string numeral = createNumeral(i);
		//cout << numeral << endl;
		for (int j = 0; j<numeral.length();j++) {
			string k = numeral.substr(j,1);
			//cout << k << endl;
			countNumerals[k]++;
		}

		
	}

	for (int i = 0; i<7;i++) {
		if (countNumerals[numerals[i]] > 0) {
			cout << numerals[i] << " " << countNumerals[numerals[i]] << endl;
			fout << numerals[i] << " " << countNumerals[numerals[i]] << endl;
		}
	}
	








	fin.close();
	fout.close();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2-t1).count()/1000000000.0;
	cout << endl << "Execution time: " << duration << " seconds" << endl;
	return 0;
}