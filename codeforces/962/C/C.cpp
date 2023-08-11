#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <math.h>
using namespace std;
typedef long long ll;


vector<vector<int>> combos;

int GetNumberOfDigits (int i)
{
    int digits = 0; 
	while (i != 0) { i/= 10; digits++; }
	return digits;
}

bool isSquare(int n) {
	int root(round(sqrt(n)));
	return n == root*root;
}

void getCombinations(vector<int>& data, int start, int end, int index, int r) {
	if (index == r) {
		combos.push_back(data);
		return;
	}
	for (int i = start; i <= end && end - i + 1 >= r-index; i++) {
		data[index] = i;
		getCombinations(data,i+1,end,index+1,r);
	}
}

void getCombos(int n, int r) {
	combos = {};
	vector<int> data(r);	
	getCombinations(data,0,GetNumberOfDigits(n)-1,0,r);
}

bool canDo(int n, vector<int>& vec) {
	
	vector<int> nvec;
	while (n != 0) {
		nvec.insert(nvec.begin(),n%10);
		n /= 10;
	}
	for (int i: vec) {
		nvec[i] = -1;
	}
	int b = 0;
	int mult = 1;
	bool seenPos = false;
	for (int i = 0; i < nvec.size(); i++) {
		if (nvec[i] > 0) seenPos = true;
		if (nvec[i] == 0 && !seenPos) return false;
	}
	for (int i = nvec.size()-1; i >= 0; i--) {
		if (nvec[i] != -1) {
			b += nvec[i]*mult;
			mult *= 10;
		}
	}
	/*
	for (int i: vec) {
		cout << i << ' ';
	}
	cout << '\n';
	cout << b << "\n\n";
	*/
	return isSquare(b);
}

bool isPoss(int n, int i) {
	getCombos(n,i);
	for (vector<int> vec: combos) {
		if (canDo(n,vec)) {
			return true;
		}
	}
	return false;
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	
	int n; cin >> n;
	if (isSquare(n)) {
		cout << 0 << '\n';
		return 0;
	}
	
	for (int i = 1; i < GetNumberOfDigits(n); i++) {
		if (isPoss(n,i)) {
			cout << i << '\n';
			return 0;
		}
	}
	cout << -1 << '\n';
	return 0;
	
	/*
	getCombos(1234,2);
	for (vector<int> vec: combos) {
		for (int i: vec) {
			cout << i << ' ';
		}
		cout << '\n';
	}
	*/
	
	
	
	return 0;
}