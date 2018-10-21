/*
ID: silxikys
PROG: test
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

ofstream fout("test.out");
ifstream fin("test.in");


int main() 
{
	vector<int> test = {1,2,3,4};
	test.erase(remove(test.begin(),test.end(),1),test.end());
	for (int i: test) {
		cout << i << ' ';
	} cout << '\n';
	vector<int>::iterator pos = find(test.begin(),test.end(),5);
	test.erase(pos,test.end());
	for (int i: test) {
		cout << i << ' ';
	} cout << '\n';

	return 0;
}