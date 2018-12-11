/*
ID: silxikys
PROG: lamps
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

void printv(vector<int> v) {
	for (int i = 1; i<v.size();i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}


bool isValidCombo(vector<int> newSeq,vector<int> onIndexes,vector<int> offIndexes) {
	for (int i = 0; i<onIndexes.size();i++) {
		if (newSeq[onIndexes[i]] == 0) return false;
	}
	for (int i = 0; i<offIndexes.size();i++) {
		if (newSeq[offIndexes[i]] == 1) return false;
	}
	return true;
}

void button1(vector<int>& seq) {
	for (int i = 1; i<seq.size();i++) {
		if (seq[i] == 0) seq[i] = 1;
		else {seq[i] = 0;}
	}

}

void button2(vector<int>& seq) {
	for (int i = 1; i<seq.size();i+=2) {
		if (seq[i] == 0) seq[i] = 1;
		else {seq[i] = 0;}
	}

}

void button3(vector<int>& seq) {
	for (int i = 2; i<seq.size();i+=2) {
		if (seq[i] == 0) seq[i] = 1;
		else {seq[i] = 0;}
	}

}

void button4(vector<int>& seq) {
	for (int i = 1; i<seq.size();i+=3) {
		if (seq[i] == 0) seq[i] = 1;
		else {seq[i] = 0;}
	}

}

int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	ofstream fout("lamps.out");
	ifstream fin("lamps.in");
	//grabs input
	vector<int> onIndexes;
	vector<int> offIndexes;
	
	int N; fin >> N;
	int C; fin >> C;

	vector<int> startSequence(N+1,1);

	int onIndex; fin >> onIndex;
	while(onIndex != -1) {
		onIndexes.push_back(onIndex);
		fin >> onIndex;
	}
	int offIndex; fin >> offIndex;
	while(offIndex != -1) {
		offIndexes.push_back(offIndex);
		fin >> offIndex;
	}
	//calculate C
	if (C > 4) {
		switch(C % 2) {
			case 0: C = 4; break;
			case 1: C = 3; break;
		}
	}
	//now try the possibilities
	vector<vector<int>> configs;
	

	vector<string> combos;
	switch(C) {
		case 0: combos = {"0000"}; break;
		case 1: combos = {"0001","0010","1000" ,"0100" }; break;
		case 2: combos = {"0110", "1100", "0101", "1001", "0011", "1010",  "0000"}; break;
		case 3: combos = {"0001", "1011","0010","1000","1110", "0100",    "1101",  "0111"}; break;
		case 4: combos = {"0110","1100", "0101","1111","1001", "0011",  "1010",  "0000"}; break;
	}


	for (int i = 0; i<combos.size();i++) {
		vector<int> copy = startSequence;
		vector<int>& copyRef = copy;
		string combo = combos[i];
		//cout << combo << endl;

		if (combo[3] == '1') button1(copyRef);
		if (combo[2] == '1') button2(copyRef);
		if (combo[1] == '1') button3(copyRef);
		if (combo[0] == '1') button4(copyRef);

		printv(copy);		

		if (isValidCombo(copy,onIndexes,offIndexes)) {
			//printv(copy);
			configs.push_back(copy);
		}
	}

	//output
	cout << configs.size() << endl;

	if (configs.size() == 0) {
		fout << "IMPOSSIBLE" << endl;
	}
	else {
	
	
	for (int i = 0; i<configs.size();i++) {
		for (int j = 1; j < configs[i].size();j++) { 
			cout << configs[i][j];
			fout << configs[i][j];
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