// Answer for “Timothy Mou”: 82 words
//This program reads the dictionary line-by-line, turns all the letters to lowercase, //and then counts how many of the words make the "isValid" function return true. 
//NAME is a const string that contains all the letters for a person’s name in //lowercase.
//the “isValid” function is only performed on words that have a length less than or //equal to the length of NAME.
//The "isValid" function creates a copy of the NAME and iterates over each character in //the given word, ignoring spaces.
//The function checks that each non-space character can be found in the NAME, and, if //so, the character is removed from the copy of the NAME (to make sure that repeated //letters do not appear more times than they appear in the NAME). Else, the function //returns false.
//If the function gets to the end of the word without returning, it returns true, and //the counter is incremented; the value of the counter at the end of the program is how //many valid words there are.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const string NAME = "kaushalgumpula";
//name: Timothy Mou

bool isValid(string word) {
	string nameCopy = NAME;
	for (int i = 0; i < word.length(); i++) {
		string letter = word.substr(i,1);
		if (letter == " ") {continue;}
		int letterIndex = nameCopy.find(letter);
		if (letterIndex == -1) {return false;}
		nameCopy.erase(nameCopy.begin()+letterIndex);
	}
	return true;
}

int main() {
	ifstream dict("english.txt");
	string word;
	int wordCounter = 0;
	while (getline(dict,word)) {
		if (word.length() <= NAME.length()) {
			//turns the letters to lowercase
			for (int i = 0; i<word.length();i++) {
			word[i] = tolower(word[i]);
			}
			if (isValid(word)) {
				wordCounter++;
			}
		}
	}
	cout << wordCounter << endl;
	dict.close();
	return 0;
}
