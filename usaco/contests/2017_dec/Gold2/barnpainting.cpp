/*
ID: silxikys
PROG: barnpainting
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cmath>
using namespace std;

ofstream fout("barnpainting.out");
ifstream fin("barnpainting.in");

int N, K;

int main() 
{
	fin >> N >> K;

	cout << ((int)pow(2,N-K) % 1000000007) << '\n';
	fout << ((int)pow(2,N-K) % 1000000007) << '\n';


	return 0;
}