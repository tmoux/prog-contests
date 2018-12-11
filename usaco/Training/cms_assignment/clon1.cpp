#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

#include <chrono>
using namespace std::chrono;

//name: Timothy Mou
const string NAME = "timothymou";
string NAMEUPPER = NAME;
map<string,int> namemap;

map<string,int> countLetters(string str) {
	map<string,int> ret;
	for (int i = 0;i<str.length();i++) {
		ret[str.substr(i,i+1)]++;
		
	}
}

bool isValid(string word) {

	string nameCopy = NAME;
	for (int i = 0;i<word.length();i++) {
		string letter = word.substr(i,i+1);
		if (letter == " ") {
			continue;
		}
		int letterIndex = nameCopy.find(letter);
		if (letterIndex == -1 && NAMEUPPER.find(letter) == -1) {
			return false;
		}
	}
	map<string,int> r = countLetters(word);
	for (map<string,int>::iterator iter = r.begin(); iter != r.end();++iter) {
		string key = iter->first;
		if (r[key] > namemap[key]) {
			return false;
		}
	}

	return true;
}

int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	ifstream dict("english.txt");

	for (int i = 0;i < NAME.length();i++) {
		NAMEUPPER[i] = toupper(NAMEUPPER[i]);
	}
	namemap = countLetters(NAME);
	for (pair<string,int> element : namemap) {
		string w = element.first;
		cout << w << " " << namemap[w] << endl;
	}
	 /*
	string word;
	int wordCounter = 0;
	while (getline(dict,word)) {
		if (word.length() <= NAME.length()) {
			if (isValid(word)) {
				wordCounter++;
				cout << word << endl;
			}
		}
		
	}
	cout << wordCounter << endl;
	
	dict.close();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2-t1).count()/1000000000.0;
	cout << endl << "Execution time: " << duration << " seconds" << endl;
*/
	return 0;
}




