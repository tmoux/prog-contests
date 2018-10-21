#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
#include <assert.h>
using namespace std;
typedef long long ll;

ofstream fout("cbarn.out");
ifstream fin("cbarn.in");

const int maxn = 100002;
int A[2*maxn];
int N;

int main() 
{
	fin >> N;
	for (int i = 1; i <= N; i++) {
		fin >> A[i];
		A[i+N] = A[i];
	}
	int minCow = maxn+5, minPos;
	int curr = 0;
	for (int i = 1; i <= N; i++) {
		curr += A[i];
		curr--;
		if (curr < minCow) {
			minCow = curr;
			minPos = i;
		}
	}
	curr = 0;
	ll res = 0LL;
	queue<int> q;
	for (int i = minPos + 1; i <= minPos + N; i++) {
		for (int j = 0; j < A[i]; j++) {
			q.push(i);
		}
		int f = q.front();
		q.pop();
		res += 1LL*(i-f)*(i-f);
	}
	cout << res << '\n';
	fout << res << '\n';

	return 0;
}