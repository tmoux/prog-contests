/*
ID: silxikys
PROG: prefix
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

//globals
vector<string> primitives;
string s = "";
int maxIndex = 0;
//////////////////////////////
int validPrefix(vector<string> primitives, string s, int length) {
	int total = 0;
	//cout << length << endl;
	if (length == 0) {
		//cout << "ok" << endl;
		return 1;
	}
	string sstr = s.substr(0,length);
	

	for (int i = 0; i<primitives.size();i++) {
		string p = primitives[i];
		if (p.length() <= sstr.length()) {
			if (p == sstr.substr(sstr.length()-p.length(),p.length())) {
			 	total += validPrefix(primitives, s, length-p.length());
			 	if (total > 0) {
			 		break;
			 	}
			}
		}
		//cout << total << endl;
	}
	return total;
}

void longestPrefix(int startIndex) {
	
	bool found = false;
	for (string p: primitives) {
			
		if (s.substr(startIndex,p.length()) == p) {
			found = true;
			//cout << startIndex + p.length() << endl;
			longestPrefix(startIndex + p.length());
		}
		
	}
	if (!found) {
		//cout << startIndex << endl;
		if (startIndex > maxIndex) {
			maxIndex = startIndex;
		}
	}
}


int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	ofstream fout("prefix.out");
	ifstream fin("prefix.in");
	
	//grab input
	string prefix; fin >> prefix;
	while (prefix != ".") {
		primitives.push_back(prefix);
		fin >> prefix;
	}
	string ssequence;
	while(getline(fin, ssequence)) {
		s += ssequence;
	}

	//cout << s.length() << endl;

	//for (int i = 0; i<primitives.size();i++) {
	//	cout << primitives[i] << " ";
	//}
	//cout << endl << s << endl;
	//
	//compute max primitive length
	int maxPrimLength = 0;
	for (string prim: primitives) {
		if (prim.length() > maxPrimLength) {
			maxPrimLength = prim.length();
		}
	}

	//compute answer
	int cache[200001];
	for (int i = 0; i<200001;i++) {
		cache[i] = -1;
	}
	bool pflag = false;
	for (int i = 0; i<primitives.size();i++) {
		if (s.substr(0,primitives[i].length()) == primitives[i]) {
			cache[primitives[i].length()-1] = primitives[i].length()-1;
			pflag = true;
		}
	}

	if (pflag == false) {
		fout << 0 << endl;
		cout << 0 << endl;
	}

	else {


	for (int i = 0; i<s.length();i++) {
		bool flag = false;
		for (int j = i-1;j>=max(0, i-maxPrimLength) && flag == false;j--) {
			if (cache[j] == j) {
				string mightBP = s.substr(j+1,i-j);
				//cout << i << " " << j << " " << mightBP << endl;
				for (string p: primitives) {
					if (p == mightBP) {
						flag = true;
						cache[i] = i;
						break;
					}
				}
			}	
		}
	}
	//output
	//for (int i = 0; i<s.length();i++) {
	//	cout << cache[i] << endl;
	//}




	for (int i = s.length()-1; i>=0;i--) {
		if (cache[i] > 0) {
			cout << cache[i]+1 << endl;
			fout << cache[i]+1 << endl;
			break;
		}
	}

	}

	
	fin.close();
	fout.close();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2-t1).count()/1000000000.0;
	cout << endl << "Execution time: " << duration << " seconds" << endl;
	return 0;
}