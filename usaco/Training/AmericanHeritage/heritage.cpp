/*
ID: silxikys
PROG: heritage
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

string postorder;

void build(string preorder, string inorder) {
	if (preorder.size() == 0) {
		return;
	}
	int pos = inorder.find(preorder[0]);
	build(preorder.substr(1,pos),inorder.substr(0,pos));
	build(preorder.substr(pos+1),inorder.substr(pos+1));
	postorder += preorder[0];
}

int main() {
	t1 = gettime();
	ofstream fout("heritage.out");
	ifstream fin("heritage.in");

	string inorder, preorder;
	fin >> inorder >> preorder;
	
	build(preorder,inorder);
	cout << postorder << endl;
	fout << postorder << endl;

	
	endProgram(t1);
	return 0;
}