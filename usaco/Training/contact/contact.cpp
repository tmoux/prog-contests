/*
ID: silxikys
PROG: contact
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

//globals
int A, B, N;
string code;

long long toValue(string s)
{
    long long val = 0;
    for (char c : s) {
        if (c == '1') {
            val = (val << 1) + 1;
        } else {
            val = val << 1;
        }
    }
    return val;
}

bool stringCompare(const string& a, const string& b) {
	if (a.length() != b.length()) {
		return (a.length() < b.length());
	}
	else {
		return (toValue(a) < toValue(b));
	}
}

int main() {
	t1 = gettime();
	ofstream fout("contact.out");
	ifstream fin("contact.in");

	fin >> A >> B >> N;

	
	string line;
	while (getline(fin, line)) {
		code += line;
	}
	if (code.length() == 1) {
		fout << 1 << endl;
		fout << 1 << endl;
	}

	map<string, int> counter;
	for (int i = 0; i < code.length(); i++) {
		for (int j = A; j <= B; j++) {
			string sub = code.substr(i,j);
			if (sub.length() != j) {
				continue;
			}
			if (counter.find(sub) == counter.end()) {
				counter[sub] = 0;
			}
			counter[sub]++;
		}
	}
	
	map<int, vector<string>> patterns;
	for (auto const& x : counter) {
    	if (patterns.find(x.second) == patterns.end()) {
    		patterns[x.second] = vector<string> {};
    	}
    	patterns[x.second].push_back(x.first);
	}

	int c = 0;
	vector<pair<int,vector<string>>> output;
	for (auto const& x : patterns) {
		if (c >= patterns.size()-N) {
			output.push_back(make_pair(x.first,x.second));			
		}
		c++;
	}
	
	for (int i = output.size()-1; i >= 0; i--) {
		pair<int,vector<string>> p = output[i];
		sort(p.second.begin(),p.second.end(),stringCompare);
		cout << p.first << endl;
		fout << p.first << endl;
		for (int j = 0; j < p.second.size(); j++) {
			cout << p.second[j];
			fout << p.second[j];
			if (j % 6 == 5) {
				cout << endl;
				fout << endl;
			}
			else if (j < p.second.size()-1){
				cout << " ";
				fout << " ";
			}
		}
		cout << endl;
		fout << endl;
	}

	
	endProgram(t1);
	return 0;
}