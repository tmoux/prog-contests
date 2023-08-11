#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;



int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	string A; cin >> A;
	string B = A;
	for (int i = 0; i < B.size()/2; i++) {
		char temp = B[i];
		B[i] = B[B.size()-1-i];
		B[B.size()-1-i] = temp;
	}
	cout << (A+B) << '\n';
	
	return 0;
}