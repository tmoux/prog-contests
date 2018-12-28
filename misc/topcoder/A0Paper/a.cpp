#include <bits/stdc++.h>
using namespace std;
class A0Paper
{
public:
	string canBuild(vector<int> A) {
		int n = A.size();
		for (int i = n - 1; i > 0; i--) {
			A[i-1] += A[i]/2;
		}
		return (A[0] > 0)?:"Possible":"Impossible";
	}
};