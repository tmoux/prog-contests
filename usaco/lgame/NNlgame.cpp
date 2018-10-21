/*
ID: silxikys
PROG: lgame
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
string NAME;

map<char,int> valueOf = {
	{'q',7},
	{'w',6},
	{'e',1},
	{'r',2},
	{'t',2},
	{'y',5},
	{'u',4},
	{'i',1},
	{'o',3},
	{'p',5},
	{'a',2},
	{'s',1},
	{'d',4},
	{'f',6},
	{'g',5},
	{'h',5},
	{'j',7},
	{'k',6},
	{'l',3},
	{'z',7},
	{'x',7},
	{'c',4},
	{'v',6},
	{'b',5},
	{'n',2},
	{'m',5}
};

bool isValid(string word, string nameCopy) {
	for (int i = 0; i < word.length(); i++) {
		string letter = word.substr(i,1);
		if (letter == " ") {continue;}
		int letterIndex = nameCopy.find(letter);
		if (letterIndex == -1) {return false;}
		nameCopy.erase(nameCopy.begin()+letterIndex);
	}
	return true;
}

int getValue(string word) {
	int total = 0;
	for (char c: word) {
		total += valueOf[c];
	}
	return total;
}

string complement(string word) {
	string nameCopy = NAME;
	for (char c: word) {
		nameCopy.erase(nameCopy.find(c),1);
	}
	return nameCopy;
}

int main() {
	ifstream dict("lgame.dict");
	ifstream fin("lgame.in");
	ofstream fout("lgame.out");

	//input
	fin >> NAME;

	//get valid words
	vector<string> validWords;
	string word;
	while (getline(dict,word)) {
		if (word.length() <= NAME.length()) {
			if (isValid(word, NAME)) {
				validWords.push_back(word);
			}
		}
	}

	//compute answers
	vector<pair<string,string>> answers;
	int maxsum = 0;
	for (string w: validWords) {
		//cout << w << endl;
		int v1 = getValue(w);
		string comp = complement(w);
		int maxComplement = 0;
		vector<string> maxc;
		for (string qw: validWords) {
			if (isValid(qw,comp) && getValue(qw) > maxComplement) {
				maxComplement = getValue(qw);
				maxc = {qw};
			}
			else if (isValid(qw,comp) && getValue(qw) == maxComplement) {
				maxc.push_back(qw);
			}
		}

		if (maxc.size() == 0) {
			maxc = {""};
		}

		vector<pair<string,string>> toAdd;
		for (string s: maxc) {
			if (s == "") {
				toAdd.push_back(make_pair(w,""));
			}
			else if (w < s) {
				toAdd.push_back(make_pair(w,s));
			}
			else {
				toAdd.push_back(make_pair(s,w));
			}
		}
		if (v1 + maxComplement > maxsum) {
			maxsum = v1 + maxComplement;
			answers = toAdd;
		}
		else if (v1 + maxComplement == maxsum) {
			for (pair<string,string> p : toAdd) {
				if (find(answers.begin(),answers.end(),p) == answers.end()) {
					answers.push_back(p);
				}
			}
		}
	}




	//output
	sort(answers.begin(), answers.end(), [](const pair<string,string> &left, const pair<string,string> &right) {
    	if (left.first != right.first) {
    		return left.first < right.first;
    	}
    	else {
    		return left.second < right.second;
    	}
	});

	cout << maxsum << endl;
	fout << maxsum << endl;
	for (pair<string,string> p: answers) {
		cout << p.first << " " << p.second << endl;
		fout << p.first;
		if (p.second.length() != 0) {
			fout << " " << p.second;
		}
		fout << endl;


	}
	
	fin.close();
	fout.close();
	dict.close();
	return 0;
}