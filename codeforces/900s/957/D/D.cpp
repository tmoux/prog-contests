#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const long long maxn = 100005;
long long N;
long long numAbove[maxn];
long long minNumMarks[maxn];


int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//	freopen("input.in","r",stdin);
	cin >> N;
	for (long long i = 0; i < N; i++) {
		cin >> numAbove[i];
	}
	for (long long i = 0; i < N; i++) {
		if (i == 0) {
			minNumMarks[i] = 1;
		}
		else {
			minNumMarks[i] = max(minNumMarks[i-1],numAbove[i]+1);
		}
	}
	for (long long i = N-1; i >= 0; i--) {
		if (minNumMarks[i] < minNumMarks[i+1]-1) {
			minNumMarks[i] = minNumMarks[i+1]-1;
		}
	}
	/*
	for (long long i = 0; i < N; i++) {
		cout << minNumMarks[i] << '\n';
	}
	*/
	
	long long sum = 0;
	for (long long i = 0; i < N; i++) {
		sum += minNumMarks[i] - (numAbove[i]+1);
	}
	cout << sum << '\n';
	
	
	return 0;
}

